#include "nfc_blank_card_scene.h"

#include <furi.h>

#define ADD_SCENE(name, id)                                                              \
    void nfc_blank_card_scene_##name##_on_enter(void* context);                          \
    bool nfc_blank_card_scene_##name##_on_event(void* context, SceneManagerEvent event); \
    void nfc_blank_card_scene_##name##_on_exit(void* context);
#include "nfc_blank_card_scene_config.h"
#undef ADD_SCENE

static const AppSceneOnEnterCallback nfc_blank_card_on_enter_handlers[] = {
#define ADD_SCENE(name, id) nfc_blank_card_scene_##name##_on_enter,
#include "nfc_blank_card_scene_config.h"
#undef ADD_SCENE
};

static const AppSceneOnEventCallback nfc_blank_card_on_event_handlers[] = {
#define ADD_SCENE(name, id) nfc_blank_card_scene_##name##_on_event,
#include "nfc_blank_card_scene_config.h"
#undef ADD_SCENE
};

static const AppSceneOnExitCallback nfc_blank_card_on_exit_handlers[] = {
#define ADD_SCENE(name, id) nfc_blank_card_scene_##name##_on_exit,
#include "nfc_blank_card_scene_config.h"
#undef ADD_SCENE
};

const SceneManagerHandlers nfc_blank_card_scene_manager_handlers = {
    .on_enter_handlers = nfc_blank_card_on_enter_handlers,
    .on_event_handlers = nfc_blank_card_on_event_handlers,
    .on_exit_handlers = nfc_blank_card_on_exit_handlers,
    .scene_num = COUNT_OF(nfc_blank_card_on_enter_handlers),
};
