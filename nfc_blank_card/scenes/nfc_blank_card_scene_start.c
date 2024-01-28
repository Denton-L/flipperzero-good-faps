#include "../nfc_blank_card.h"
#include "nfc_blank_card_scene_i.h"

struct SubmenuScene {
    const char* label;
    uint32_t scene_id;
};

static const struct SubmenuScene submenu_scenes[] = {
    {
        .label = "Reset NFC Tag to Blank",
        .scene_id = NFCBlankCardAppSceneStart,
    },
    {
        .label = "Write to Blank NFC Tag",
        .scene_id = NFCBlankCardAppSceneStart,
    },
    {
        .label = NULL,
    },
};

void nfc_blank_card_scene_start_submenu_callback(void* context, uint32_t index) {
    struct NFCBlankCardApp* instance = context;
    view_dispatcher_send_custom_event(instance->view_dispatcher, index);
}

void nfc_blank_card_scene_start_on_enter(void* context) {
    struct NFCBlankCardApp* instance = context;

    Submenu* submenu = instance->submenu;

    uint32_t index = 0;
    for(const struct SubmenuScene* scene = submenu_scenes; scene->label; scene++) {
        submenu_add_item(
            submenu, scene->label, index++, nfc_blank_card_scene_start_submenu_callback, instance);
    }

    view_dispatcher_switch_to_view(instance->view_dispatcher, NFCBlankCardAppViewSubmenu);
}

bool nfc_blank_card_scene_start_on_event(void* context, SceneManagerEvent event) {
    struct NFCBlankCardApp* instance = context;

    if(event.type != SceneManagerEventTypeCustom) {
        return false;
    }

    scene_manager_next_scene(instance->scene_manager, submenu_scenes[event.event].scene_id);
    return true;
}

void nfc_blank_card_scene_start_on_exit(void* context) {
    struct NFCBlankCardApp* instance = context;

    submenu_reset(instance->submenu);
}
