#include "../nfc_blank_card.h"

#include <furi.h>
#include <gui/scene_manager.h>

void nfc_blank_card_scene_start_on_enter(void* context) {
    struct NFCBlankCardApp* instance = context;
    UNUSED(instance);
}

bool nfc_blank_card_scene_start_on_event(void* context, SceneManagerEvent event) {
    struct NFCBlankCardApp* instance = context;
    UNUSED(instance);
    UNUSED(event);
    return false;
}

void nfc_blank_card_scene_start_on_exit(void* context) {
    struct NFCBlankCardApp* instance = context;
    UNUSED(instance);
}
