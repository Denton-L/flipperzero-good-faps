#include "../mf_classic_blank.h"

#include <mf_classic_blank_icons.h>

static void mf_classic_blank_poller_callback(void* context, enum MfClassicBlankPollerEvent event) {
    struct MfClassicBlankApp* instance = context;
    UNUSED(instance);
    UNUSED(event);
}

void mf_classic_blank_scene_reset_on_enter(void* context) {
    struct MfClassicBlankApp* instance = context;

    popup_set_icon(instance->popup, 0, 8, &I_NFC_manual_60x50);
    popup_set_text(instance->popup, "Apply card to\nthe back", 128, 32, AlignRight, AlignCenter);

    mf_classic_blank_app_blink_start(instance);
    mf_classic_blank_poller_start(
        instance->mf_classic_blank_poller, mf_classic_blank_poller_callback, instance);
    view_dispatcher_switch_to_view(instance->view_dispatcher, MfClassicBlankAppViewPopup);
}

bool mf_classic_blank_scene_reset_on_event(void* context, SceneManagerEvent event) {
    struct MfClassicBlankApp* instance = context;

    if(event.type != SceneManagerEventTypeCustom) {
        return false;
    }

    UNUSED(instance);
    UNUSED(event);

    return false;
}

void mf_classic_blank_scene_reset_on_exit(void* context) {
    struct MfClassicBlankApp* instance = context;

    mf_classic_blank_poller_stop(instance->mf_classic_blank_poller);
    mf_classic_blank_app_blink_stop(instance);
    popup_reset(instance->popup);
}
