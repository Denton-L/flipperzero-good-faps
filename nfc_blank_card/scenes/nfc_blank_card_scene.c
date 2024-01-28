#include "nfc_blank_card_scene.h"

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(*array))

void nfc_blank_card_scene_start_on_enter(void* context);

static const AppSceneOnEnterCallback nfc_blank_card_on_enter_handlers[] = {
    nfc_blank_card_scene_start_on_enter,
};

bool nfc_blank_card_scene_start_on_event(void* context, SceneManagerEvent event);

static const AppSceneOnEventCallback nfc_blank_card_on_event_handlers[] = {
    nfc_blank_card_scene_start_on_event,
};

void nfc_blank_card_scene_start_on_exit(void* context);

static const AppSceneOnExitCallback nfc_blank_card_on_exit_handlers[] = {
    nfc_blank_card_scene_start_on_exit,
};

const SceneManagerHandlers nfc_blank_card_scene_manager_handlers = {
    .on_enter_handlers = nfc_blank_card_on_enter_handlers,
    .on_event_handlers = nfc_blank_card_on_event_handlers,
    .on_exit_handlers = nfc_blank_card_on_exit_handlers,
    .scene_num = ARRAY_LENGTH(nfc_blank_card_on_enter_handlers),
};

bool nfc_blank_card_scene_handlers_is_correct(void) {
    return nfc_blank_card_scene_manager_handlers.scene_num ==
               ARRAY_LENGTH(nfc_blank_card_on_enter_handlers) &&
           nfc_blank_card_scene_manager_handlers.scene_num ==
               ARRAY_LENGTH(nfc_blank_card_on_event_handlers) &&
           nfc_blank_card_scene_manager_handlers.scene_num ==
               ARRAY_LENGTH(nfc_blank_card_on_exit_handlers);
}
