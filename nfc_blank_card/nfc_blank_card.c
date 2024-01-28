#include "nfc_blank_card.h"
#include "scenes/nfc_blank_card_scene.h"

#include <furi.h>

static bool nfc_blank_card_app_custom_event_callback(void* context, uint32_t event) {
    furi_assert(context);
    struct NFCBlankCardApp* instance = context;

    return scene_manager_handle_custom_event(instance->scene_manager, event);
}

static bool nfc_blank_card_app_back_event_callback(void* context) {
    furi_assert(context);
    struct NFCBlankCardApp* instance = context;

    return scene_manager_handle_back_event(instance->scene_manager);
}

static void nfc_blank_card_app_tick_event_callback(void* context) {
    furi_assert(context);
    struct NFCBlankCardApp* instance = context;

    scene_manager_handle_tick_event(instance->scene_manager);
}

struct NFCBlankCardApp* nfc_blank_card_app_alloc(void) {
    struct NFCBlankCardApp* instance = malloc(sizeof(*instance));

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

    instance->submenu = submenu_alloc();
    view_dispatcher_add_view(
        instance->view_dispatcher,
        NFCBlankCardAppViewSubmenu,
        submenu_get_view(instance->submenu));

    instance->popup = popup_alloc();
    view_dispatcher_add_view(
        instance->view_dispatcher, NFCBlankCardAppViewPopup, popup_get_view(instance->popup));

    return instance;
}

void nfc_blank_card_app_free(struct NFCBlankCardApp* instance) {
    furi_assert(instance);

    view_dispatcher_remove_view(instance->view_dispatcher, NFCBlankCardAppViewPopup);
    popup_free(instance->popup);

    view_dispatcher_remove_view(instance->view_dispatcher, NFCBlankCardAppViewSubmenu);
    submenu_free(instance->submenu);

    instance->gui = NULL;
    furi_record_close(RECORD_GUI);

    view_dispatcher_free(instance->view_dispatcher);
    scene_manager_free(instance->scene_manager);

    free(instance);
}
