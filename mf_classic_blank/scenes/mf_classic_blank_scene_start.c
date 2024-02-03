#include "../mf_classic_blank.h"
#include "mf_classic_blank_scene_i.h"

struct SubmenuScene {
    const char* label;
    uint32_t scene_id;
};

static const struct SubmenuScene submenu_scenes[] = {
    {
        .label = "Reset Nfc Tag to Blank",
        .scene_id = MfClassicBlankAppSceneReset,
    },
    {
        .label = "Write to Blank Nfc Tag", // TODO
        .scene_id = -1,
    },
    {
        .label = NULL,
    },
};

void mf_classic_blank_scene_start_submenu_callback(void* context, uint32_t index) {
    struct MfClassicBlankApp* instance = context;
    view_dispatcher_send_custom_event(instance->view_dispatcher, index);
}

void mf_classic_blank_scene_start_on_enter(void* context) {
    struct MfClassicBlankApp* instance = context;

    Submenu* submenu = instance->submenu;

    uint32_t index = 0;
    for(const struct SubmenuScene* scene = submenu_scenes; scene->label; scene++) {
        submenu_add_item(
            submenu, scene->label, index++, mf_classic_blank_scene_start_submenu_callback, instance);
    }

    view_dispatcher_switch_to_view(instance->view_dispatcher, MfClassicBlankAppViewSubmenu);
}

bool mf_classic_blank_scene_start_on_event(void* context, SceneManagerEvent event) {
    struct MfClassicBlankApp* instance = context;

    if(event.type != SceneManagerEventTypeCustom) {
        return false;
    }

    scene_manager_next_scene(instance->scene_manager, submenu_scenes[event.event].scene_id);
    return true;
}

void mf_classic_blank_scene_start_on_exit(void* context) {
    struct MfClassicBlankApp* instance = context;

    submenu_reset(instance->submenu);
}
