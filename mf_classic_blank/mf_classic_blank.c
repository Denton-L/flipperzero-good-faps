#include "lib/mf_classic_blank/mf_classic_blank_device.h"
#include "mf_classic_blank.h"
#include "scenes/mf_classic_blank_scene.h"

#include <notification/notification_messages.h>

const struct MfClassicBlankAppMode mf_classic_blank_app_modes[] = {
    {
        .label = "Reset Nfc Tag to Blank",
        .device_check = mf_classic_blank_device_blankable,
    },
    {
        .label = "Write to Blank Nfc Tag",
        .device_check = mf_classic_blank_device_writable,
    },
    {
        .label = NULL,
    },
};

static bool mf_classic_blank_app_custom_event_callback(void* context, uint32_t event) {
    struct MfClassicBlankApp* instance = context;

    return scene_manager_handle_custom_event(instance->scene_manager, event);
}

static bool mf_classic_blank_app_back_event_callback(void* context) {
    struct MfClassicBlankApp* instance = context;

    return scene_manager_handle_back_event(instance->scene_manager);
}

static void mf_classic_blank_app_tick_event_callback(void* context) {
    struct MfClassicBlankApp* instance = context;

    scene_manager_handle_tick_event(instance->scene_manager);
}

struct MfClassicBlankApp* mf_classic_blank_app_alloc(void) {
    struct MfClassicBlankApp* instance = malloc(sizeof(*instance));

    instance->scene_manager =
        scene_manager_alloc(&mf_classic_blank_scene_manager_handlers, instance);
    instance->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(instance->view_dispatcher);
    view_dispatcher_set_event_callback_context(instance->view_dispatcher, instance);
    view_dispatcher_set_custom_event_callback(
        instance->view_dispatcher, mf_classic_blank_app_custom_event_callback);
    view_dispatcher_set_navigation_event_callback(
        instance->view_dispatcher, mf_classic_blank_app_back_event_callback);
    view_dispatcher_set_tick_event_callback(
        instance->view_dispatcher, mf_classic_blank_app_tick_event_callback, 100);

    instance->dialogs_app = furi_record_open(RECORD_DIALOGS);
    instance->gui = furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(
        instance->view_dispatcher, instance->gui, ViewDispatcherTypeFullscreen);
    instance->storage = furi_record_open(RECORD_STORAGE);
    instance->notification_app = furi_record_open(RECORD_NOTIFICATION);

    instance->submenu = submenu_alloc();
    view_dispatcher_add_view(
        instance->view_dispatcher,
        MfClassicBlankAppViewSubmenu,
        submenu_get_view(instance->submenu));

    instance->popup = popup_alloc();
    view_dispatcher_add_view(
        instance->view_dispatcher, MfClassicBlankAppViewPopup, popup_get_view(instance->popup));

    instance->file_path = furi_string_alloc_set_str(NFC_APP_FOLDER);
    instance->source_nfc_device = nfc_device_alloc();
    // TODO: do we gotta set the loading callback here?

    instance->nfc = nfc_alloc();
    instance->mf_classic_blank_poller = mf_classic_blank_poller_alloc(instance->nfc);

    return instance;
}

void mf_classic_blank_app_free(struct MfClassicBlankApp* instance) {
    mf_classic_blank_poller_free(instance->mf_classic_blank_poller);
    nfc_free(instance->nfc);

    nfc_device_free(instance->source_nfc_device);
    furi_string_free(instance->file_path);

    view_dispatcher_remove_view(instance->view_dispatcher, MfClassicBlankAppViewPopup);
    popup_free(instance->popup);

    view_dispatcher_remove_view(instance->view_dispatcher, MfClassicBlankAppViewSubmenu);
    submenu_free(instance->submenu);

    furi_record_close(RECORD_STORAGE);
    furi_record_close(RECORD_NOTIFICATION);
    furi_record_close(RECORD_GUI);
    furi_record_close(RECORD_DIALOGS);

    view_dispatcher_free(instance->view_dispatcher);
    scene_manager_free(instance->scene_manager);

    free(instance);
}

void mf_classic_blank_app_blink_start(struct MfClassicBlankApp* instance) {
    notification_message(instance->notification_app, &sequence_blink_start_cyan);
}

void mf_classic_blank_app_blink_stop(struct MfClassicBlankApp* instance) {
    notification_message(instance->notification_app, &sequence_blink_stop);
}
