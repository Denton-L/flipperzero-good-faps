#include "nfc_blank_card_scanner.h"

#include <furi.h>
#include <nfc/nfc.h>

enum NfcBlankCardScannerState {
    NfcBlankCardScannerStateIdle,
    NfcBlankCardScannerStateActive,
    NfcBlankCardScannerStateStopRequest,
};

struct NfcBlankCardScanner {
    Nfc* nfc;

    enum NfcBlankCardScannerState state;
    FuriMutex* state_mutex;

    NfcBlankCardScannerCallback callback;
    void* context;
    FuriThread* worker;
};

struct NfcBlankCardScanner* nfc_blank_card_scanner_alloc(void) {
    struct NfcBlankCardScanner* instance = malloc(sizeof(*instance));

    instance->nfc = nfc_alloc();

    instance->state = NfcBlankCardScannerStateIdle;
    instance->state_mutex = furi_mutex_alloc(FuriMutexTypeNormal);

    return instance;
}

void nfc_blank_card_scanner_free(struct NfcBlankCardScanner* instance) {
    furi_mutex_free(instance->state_mutex);

    nfc_free(instance->nfc);

    free(instance);
}

static bool poller_detect(Nfc* nfc) {
    UNUSED(nfc);
    return false;
}

static int32_t nfc_blank_card_scanner_worker(void* context) {
    struct NfcBlankCardScanner* instance = context;

    for(;;) {
        furi_mutex_acquire(instance->state_mutex, 0);
        enum NfcBlankCardScannerState state = instance->state;
        furi_mutex_release(instance->state_mutex);
        if (state != NfcBlankCardScannerStateActive) {
            break;
        }

        if(poller_detect(instance->nfc)) {
            enum NfcBlankCardScannerEvent event = NfcBlankCardScannerEventTypeDetected;
            instance->callback(instance->context, event);
            break;
        }
    }

    furi_mutex_acquire(instance->state_mutex, 0);
    instance->state = NfcBlankCardScannerStateIdle;
    furi_mutex_release(instance->state_mutex);

    return 0;
}

static bool nfc_blank_card_scanner_check_and_set(struct NfcBlankCardScanner* instance, enum NfcBlankCardScannerState check, enum NfcBlankCardScannerState set) {
    bool check_failed = true;

    furi_mutex_acquire(instance->state_mutex, 0);
    if (instance->state == check) {
        instance->state = set;
        check_failed = false;
    }
    furi_mutex_release(instance->state_mutex);

    return check_failed;
}

void nfc_blank_card_scanner_start(struct NfcBlankCardScanner* instance, NfcBlankCardScannerCallback callback, void* context) {
    if (nfc_blank_card_scanner_check_and_set(instance, NfcBlankCardScannerStateIdle, NfcBlankCardScannerStateActive)) {
        return;
    }

    instance->callback = callback;
    instance->context = context;

    instance->worker = furi_thread_alloc();
    furi_thread_set_name(instance->worker, "NfcBlankCardScannerWorker");
    furi_thread_set_context(instance->worker, instance);
    furi_thread_set_stack_size(instance->worker, 4 * 1024);
    furi_thread_set_callback(instance->worker, nfc_blank_card_scanner_worker);
    furi_thread_start(instance->worker);
}

void nfc_blank_card_scanner_stop(struct NfcBlankCardScanner* instance) {
    if (nfc_blank_card_scanner_check_and_set(instance, NfcBlankCardScannerStateActive, NfcBlankCardScannerStateStopRequest)) {
        return;
    }

    furi_thread_join(instance->worker);
    furi_thread_free(instance->worker);
    instance->worker = NULL;

    instance->context = NULL;
    instance->callback = NULL;
}
