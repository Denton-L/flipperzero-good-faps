#include "../nfc_blank_card.h"

#include <nfc_blank_card_icons.h>

static void nfc_blank_card_poller_callback(void* context, enum NfcBlankCardPollerEvent event) {
    struct NfcBlankCardApp* instance = context;
    UNUSED(instance);
    UNUSED(event);
}

void nfc_blank_card_scene_reset_on_enter(void* context) {
    struct NfcBlankCardApp* instance = context;

    popup_set_icon(instance->popup, 0, 8, &I_NFC_manual_60x50);
    popup_set_text(instance->popup, "Apply card to\nthe back", 128, 32, AlignRight, AlignCenter);

    nfc_blank_card_app_blink_start(instance);
    nfc_blank_card_poller_start(
        instance->nfc_blank_card_poller, nfc_blank_card_poller_callback, instance);
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

    nfc_blank_card_poller_stop(instance->nfc_blank_card_poller);
    nfc_blank_card_app_blink_stop(instance);
    popup_reset(instance->popup);
}
