#include "../nfc_blank_card.h"
#include "nfc_blank_card_scene_i.h"

struct SubmenuScene {
    const char* label;
    uint32_t scene_id;
};

static const struct SubmenuScene submenu_scenes[] = {
    {
        .label = "Reset Nfc Tag to Blank",
        .scene_id = NfcBlankCardAppSceneReset,
    },
    {
        .label = "Write to Blank Nfc Tag", // TODO
        .scene_id = -1,
    },
    {
        .label = NULL,
    },
};

void nfc_blank_card_scene_start_submenu_callback(void* context, uint32_t index) {
    struct NfcBlankCardApp* instance = context;
    view_dispatcher_send_custom_event(instance->view_dispatcher, index);
}

void nfc_blank_card_scene_start_on_enter(void* context) {
    struct NfcBlankCardApp* instance = context;

    Submenu* submenu = instance->submenu;

    uint32_t index = 0;
    for(const struct SubmenuScene* scene = submenu_scenes; scene->label; scene++) {
        submenu_add_item(
            submenu, scene->label, index++, nfc_blank_card_scene_start_submenu_callback, instance);
    }

    view_dispatcher_switch_to_view(instance->view_dispatcher, NfcBlankCardAppViewSubmenu);
}

bool nfc_blank_card_scene_start_on_event(void* context, SceneManagerEvent event) {
    struct NfcBlankCardApp* instance = context;

    if(event.type != SceneManagerEventTypeCustom) {
        return false;
    }

    scene_manager_next_scene(instance->scene_manager, submenu_scenes[event.event].scene_id);
    return true;
}

void nfc_blank_card_scene_start_on_exit(void* context) {
    struct NfcBlankCardApp* instance = context;

    submenu_reset(instance->submenu);
}
