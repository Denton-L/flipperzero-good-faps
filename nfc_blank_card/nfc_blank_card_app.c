#include "nfc_blank_card.h"

int32_t nfc_blank_card_app(void* p) {
    UNUSED(p);

    struct NFCBlankCardApp* instance = nfc_blank_card_app_alloc();
    scene_manager_next_scene(instance->scene_manager, 0);
    view_dispatcher_run(instance->view_dispatcher);
    nfc_blank_card_app_free(instance);

    return 0;
}
