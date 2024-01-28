#include "../nfc_blank_card.h"

#include <nfc_blank_card_icons.h>

void nfc_blank_card_scene_reset_on_enter(void* context) {
    struct NfcBlankCardApp* instance = context;

    popup_set_icon(instance->popup, 0, 8, &I_NFC_manual_60x50);
    popup_set_text(instance->popup, "Apply card to\nthe back", 128, 32, AlignRight, AlignCenter);

    nfc_blank_card_app_blink_start(instance);

    //nfc_magic_scanner_start(instance->scanner, nfc_magic_check_worker_callback, instance);

    view_dispatcher_switch_to_view(instance->view_dispatcher, NfcBlankCardAppViewPopup);
}

bool nfc_blank_card_scene_reset_on_event(void* context, SceneManagerEvent event) {
    struct NfcBlankCardApp* instance = context;

    if(event.type != SceneManagerEventTypeCustom) {
        return false;
    }

    UNUSED(instance);
    UNUSED(event);

    return false;
}

void nfc_blank_card_scene_reset_on_exit(void* context) {
    struct NfcBlankCardApp* instance = context;

    nfc_blank_card_app_blink_stop(instance);
    popup_reset(instance->popup);
}
