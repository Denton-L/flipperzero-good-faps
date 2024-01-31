#include "nfc_blank_card.h"
#include "scenes/nfc_blank_card_scene.h"

#include <notification/notification_messages.h>

static bool nfc_blank_card_app_custom_event_callback(void* context, uint32_t event) {
    struct NfcBlankCardApp* instance = context;

    return scene_manager_handle_custom_event(instance->scene_manager, event);
}

static bool nfc_blank_card_app_back_event_callback(void* context) {
    struct NfcBlankCardApp* instance = context;

    return scene_manager_handle_back_event(instance->scene_manager);
}

static void nfc_blank_card_app_tick_event_callback(void* context) {
    struct NfcBlankCardApp* instance = context;

    scene_manager_handle_tick_event(instance->scene_manager);
}

struct NfcBlankCardApp* nfc_blank_card_app_alloc(void) {
    struct NfcBlankCardApp* instance = malloc(sizeof(*instance));

    instance->scene_manager =
        scene_manager_alloc(&nfc_blank_card_scene_manager_handlers, instance);
    instance->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(instance->view_dispatcher);
    view_dispatcher_set_event_callback_context(instance->view_dispatcher, instance);
    view_dispatcher_set_custom_event_callback(
        instance->view_dispatcher, nfc_blank_card_app_custom_event_callback);
    view_dispatcher_set_navigation_event_callback(
        instance->view_dispatcher, nfc_blank_card_app_back_event_callback);
    view_dispatcher_set_tick_event_callback(
        instance->view_dispatcher, nfc_blank_card_app_tick_event_callback, 100);

    instance->gui = furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(
        instance->view_dispatcher, instance->gui, ViewDispatcherTypeFullscreen);

    instance->notification_app = furi_record_open(RECORD_NOTIFICATION);

    instance->submenu = submenu_alloc();
    view_dispatcher_add_view(
        instance->view_dispatcher,
        NfcBlankCardAppViewSubmenu,
        submenu_get_view(instance->submenu));

    instance->popup = popup_alloc();
    view_dispatcher_add_view(
        instance->view_dispatcher, NfcBlankCardAppViewPopup, popup_get_view(instance->popup));

    instance->nfc = nfc_alloc();
    instance->nfc_blank_card_poller = nfc_blank_card_poller_alloc(instance->nfc);

    instance->nfc_device = nfc_device_alloc();
    // TODO: do we gotta set the loading callback here?

    return instance;
}

void nfc_blank_card_app_free(struct NfcBlankCardApp* instance) {
    nfc_device_free(instance->nfc_device);

    nfc_blank_card_poller_free(instance->nfc_blank_card_poller);
    nfc_free(instance->nfc);

    view_dispatcher_remove_view(instance->view_dispatcher, NfcBlankCardAppViewPopup);
    popup_free(instance->popup);

    view_dispatcher_remove_view(instance->view_dispatcher, NfcBlankCardAppViewSubmenu);
    submenu_free(instance->submenu);

    furi_record_close(RECORD_NOTIFICATION);
    furi_record_close(RECORD_GUI);

    view_dispatcher_free(instance->view_dispatcher);
    scene_manager_free(instance->scene_manager);

    free(instance);
}

void nfc_blank_card_app_blink_start(struct NfcBlankCardApp* instance) {
    notification_message(instance->notification_app, &sequence_blink_start_cyan);
}

void nfc_blank_card_app_blink_stop(struct NfcBlankCardApp* instance) {
    notification_message(instance->notification_app, &sequence_blink_stop);
}
