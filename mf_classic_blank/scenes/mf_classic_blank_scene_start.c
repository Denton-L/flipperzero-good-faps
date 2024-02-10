#include "../mf_classic_blank.h"
#include "mf_classic_blank_scene_lib.h"

void mf_classic_blank_scene_start_submenu_callback(void* context, uint32_t index) {
    struct MfClassicBlankApp* instance = context;
    view_dispatcher_send_custom_event(instance->view_dispatcher, index);
}

void mf_classic_blank_scene_start_on_enter(void* context) {
    struct MfClassicBlankApp* instance = context;

    Submenu* submenu = instance->submenu;

    uint32_t index = 0;
    for(const struct MfClassicBlankAppMode* mode = mf_classic_blank_app_modes; mode->label;
        ++mode) {
        submenu_add_item(
            submenu, mode->label, index++, mf_classic_blank_scene_start_submenu_callback, instance);
    }

    view_dispatcher_switch_to_view(instance->view_dispatcher, MfClassicBlankAppViewSubmenu);
}

bool mf_classic_blank_scene_start_on_event(void* context, SceneManagerEvent event) {
    struct MfClassicBlankApp* instance = context;

    if(event.type != SceneManagerEventTypeCustom) {
        return false;
    }

    instance->mode = &mf_classic_blank_app_modes[event.event];
    scene_manager_next_scene(instance->scene_manager, MfClassicBlankAppSceneFileSelect);
    return true;
}

void mf_classic_blank_scene_start_on_exit(void* context) {
    struct MfClassicBlankApp* instance = context;

    submenu_reset(instance->submenu);
}
