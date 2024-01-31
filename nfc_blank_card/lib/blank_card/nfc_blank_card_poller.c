#include "nfc_blank_card_poller.h"

#include <furi.h>
#include <nfc/nfc_poller.h>
#include <nfc/protocols/mf_classic/mf_classic_poller.h>

static const NfcProtocol NFC_PROTOCOL = NfcProtocolMfClassic;

struct NfcBlankCardPoller {
    Nfc* nfc;

    NfcPoller* nfc_poller;
    NfcBlankCardPollerCallback callback;
    void* context;
};

struct NfcBlankCardPoller* nfc_blank_card_poller_alloc(Nfc* nfc) {
    struct NfcBlankCardPoller* instance = malloc(sizeof(*instance));

    instance->nfc = nfc;

    return instance;
}

void nfc_blank_card_poller_free(struct NfcBlankCardPoller* instance) {
    free(instance);
}

static NfcCommand nfc_blank_card_poller_callback(NfcGenericEvent event, void* context) {
    furi_assert(event.protocol == NFC_PROTOCOL, "unexpected protocol");

    MfClassicPoller* poller = event.instance;
    MfClassicPollerEvent* event_data = event.event_data;
    struct NfcBlankCardPoller* instance = context;

    FURI_LOG_I("type", "%d", event_data->type);

    UNUSED(poller);
    UNUSED(instance);

    return NfcCommandContinue;
}

void nfc_blank_card_poller_start(struct NfcBlankCardPoller* instance, NfcBlankCardPollerCallback callback, void* context) {
    instance->nfc_poller = nfc_poller_alloc(instance->nfc, NFC_PROTOCOL);
    instance->callback = callback;
    instance->context = context;

    nfc_poller_start(instance->nfc_poller, nfc_blank_card_poller_callback, instance);
}

void nfc_blank_card_poller_stop(struct NfcBlankCardPoller* instance) {
    nfc_poller_stop(instance->nfc_poller);

    instance->context = NULL;
    instance->callback = NULL;
    nfc_poller_free(instance->nfc_poller);
    instance->nfc_poller = NULL;
}
