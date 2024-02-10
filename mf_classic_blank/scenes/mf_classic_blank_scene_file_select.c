#include "../lib/mf_classic_blank/mf_classic_blank_device.h"
#include "../mf_classic_blank.h"
#include "mf_classic_blank_scene_lib.h"

#include <mf_classic_blank_icons.h>

static const char* nfc_app_extension = ".nfc";

static bool mf_classic_blank_scene_load_from_file_select(struct MfClassicBlankApp* instance) {
    DialogsFileBrowserOptions browser_options;
    dialog_file_browser_set_basic_options(&browser_options, nfc_app_extension, &I_Nfc_10px);
    browser_options.base_path = NFC_APP_FOLDER;
    browser_options.hide_dot_files = true;

    if(!dialog_file_browser_show(
           instance->dialogs_app, instance->file_path, instance->file_path, &browser_options)) {
        return false;
    }
    if(!nfc_device_load(instance->source_nfc_device, furi_string_get_cstr(instance->file_path))) {
        return false;
    }
    return true;
}

void mf_classic_blank_scene_file_select_on_enter(void* context) {
    struct MfClassicBlankApp* instance = context;

    if(!mf_classic_blank_scene_load_from_file_select(instance)) {
        scene_manager_previous_scene(instance->scene_manager);
        return;
    }

    instance->error = instance->mode->device_check(instance->source_nfc_device);
    scene_manager_next_scene(instance->scene_manager, instance->error ? MfClassicBlankAppSceneBadFile : MfClassicBlankAppSceneWriteConfirm);
}

bool mf_classic_blank_scene_file_select_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void mf_classic_blank_scene_file_select_on_exit(void* context) {
    UNUSED(context);
}
