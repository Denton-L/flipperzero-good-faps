#include "mf_classic_blank.h"

int32_t mf_classic_blank_app(void* p) {
    UNUSED(p);

    struct MfClassicBlankApp* instance = mf_classic_blank_app_alloc();
    scene_manager_next_scene(instance->scene_manager, 0);
    view_dispatcher_run(instance->view_dispatcher);
    mf_classic_blank_app_free(instance);

    return 0;
}
