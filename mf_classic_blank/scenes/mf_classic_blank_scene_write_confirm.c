#include "../mf_classic_blank.h"
#include "mf_classic_blank_scene_lib.h"

#include <gui/modules/widget.h>
#include <notification/notification_messages.h>

static void mf_classic_blank_scene_write_confirm_widget_callback(GuiButtonType result, InputType type, void* context) {
    struct MfClassicBlankApp* instance = context;

    if(type != InputTypeShort) {
        return;
    }

    view_dispatcher_send_custom_event(instance->view_dispatcher, result);
}

void mf_classic_blank_scene_write_confirm_on_enter(void* context) {
    struct MfClassicBlankApp* instance = context;

    Widget* widget = instance->widget;
    show_message(widget, "Risky operation", "This will overwrite your device!");
    widget_add_button_element(
        widget,
        GuiButtonTypeCenter,
        "Continue",
        mf_classic_blank_scene_write_confirm_widget_callback,
        instance);
    widget_add_button_element(
        widget, GuiButtonTypeLeft, "Back", mf_classic_blank_scene_write_confirm_widget_callback, instance);

    view_dispatcher_switch_to_view(instance->view_dispatcher, MfClassicBlankAppViewWidget);
}

bool mf_classic_blank_scene_write_confirm_on_event(void* context, SceneManagerEvent event) {
    struct MfClassicBlankApp* instance = context;

    if(event.type != SceneManagerEventTypeCustom) {
        return false;
    }

    switch (event.event) {
        case GuiButtonTypeLeft:
            return scene_manager_previous_scene(instance->scene_manager);
        case GuiButtonTypeRight:
            scene_manager_next_scene(instance->scene_manager, MfClassicBlankAppSceneReset);
            return true;
        default:
            return false;
    }
}

void mf_classic_blank_scene_write_confirm_on_exit(void* context) {
    struct MfClassicBlankApp* instance = context;

    widget_reset(instance->widget);
}
