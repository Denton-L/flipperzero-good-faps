#include "mf_classic_blank_scene.h"

#include <furi.h>

#define ADD_SCENE(name, id)                                                                \
    void mf_classic_blank_scene_##name##_on_enter(void* context);                          \
    bool mf_classic_blank_scene_##name##_on_event(void* context, SceneManagerEvent event); \
    void mf_classic_blank_scene_##name##_on_exit(void* context);
#include "mf_classic_blank_scene_config.h"
#undef ADD_SCENE

static const AppSceneOnEnterCallback mf_classic_blank_on_enter_handlers[] = {
#define ADD_SCENE(name, id) mf_classic_blank_scene_##name##_on_enter,
#include "mf_classic_blank_scene_config.h"
#undef ADD_SCENE
};

static const AppSceneOnEventCallback mf_classic_blank_on_event_handlers[] = {
#define ADD_SCENE(name, id) mf_classic_blank_scene_##name##_on_event,
#include "mf_classic_blank_scene_config.h"
#undef ADD_SCENE
};

static const AppSceneOnExitCallback mf_classic_blank_on_exit_handlers[] = {
#define ADD_SCENE(name, id) mf_classic_blank_scene_##name##_on_exit,
#include "mf_classic_blank_scene_config.h"
#undef ADD_SCENE
};

const SceneManagerHandlers mf_classic_blank_scene_manager_handlers = {
    .on_enter_handlers = mf_classic_blank_on_enter_handlers,
    .on_event_handlers = mf_classic_blank_on_event_handlers,
    .on_exit_handlers = mf_classic_blank_on_exit_handlers,
    .scene_num = COUNT_OF(mf_classic_blank_on_enter_handlers),
};
