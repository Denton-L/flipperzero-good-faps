#include "nfc_blank_card.h"

struct NFCBlankCardApp* nfc_blank_card_app_alloc(void) {
    struct NFCBlankCardApp* instance = malloc(sizeof(*instance));

    return instance;
}

void nfc_blank_card_app_free(struct NFCBlankCardApp* instance) {
    furi_assert(instance);

    free(instance);
}

int32_t nfc_blank_card_app(void* p) {
    UNUSED(p);

    struct NFCBlankCardApp* instance = nfc_blank_card_app_alloc();

    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm nfc_blank_card!");

    nfc_blank_card_app_free(instance);

    return 0;
}
