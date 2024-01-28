#include "../nfc_blank_card.h"
#include "nfc_blank_card_scene_lib.h"

#include <furi.h>

void nfc_blank_card_scene_start_submenu_callback(void* context, uint32_t index) {
    UNUSED(context);
    UNUSED(index);
}

struct SubmenuItem submenu_items[] = {
    {
        .label = "Reset NFC Tag to Blank",
        .callback = nfc_blank_card_scene_start_submenu_callback,
    },
    {
        .label = "Write to Blank NFC Tag",
        .callback = nfc_blank_card_scene_start_submenu_callback,
    },
    {
        .label = NULL,
        .callback = NULL,
    },
};

void nfc_blank_card_scene_start_on_enter(void* context) {
    struct NFCBlankCardApp* instance = context;

    Submenu* submenu = instance->submenu;
    submenu_add_items(submenu, instance, submenu_items);
}

bool nfc_blank_card_scene_start_on_event(void* context, SceneManagerEvent event) {
    struct NFCBlankCardApp* instance = context;

    UNUSED(instance);
    UNUSED(event);

    return false;
}

void nfc_blank_card_scene_start_on_exit(void* context) {
    struct NFCBlankCardApp* instance = context;

    submenu_reset(instance->submenu);
}
