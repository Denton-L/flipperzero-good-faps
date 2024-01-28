#include "nfc_blank_card_scanner.h"

#include <furi.h>
#include <nfc/nfc.h>

struct NfcBlankCardScanner {
    Nfc* nfc;
};

struct NfcBlankCardScanner* nfc_blank_card_scanner_alloc(void) {
    struct NfcBlankCardScanner* instance = malloc(sizeof(*instance));

    instance->nfc = nfc_alloc();

    return instance;
}

void nfc_blank_card_scanner_free(struct NfcBlankCardScanner* instance) {
    nfc_free(instance->nfc);

    free(instance);
}
