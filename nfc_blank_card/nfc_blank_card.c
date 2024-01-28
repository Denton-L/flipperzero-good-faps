#include "nfc_blank_card.h"
#include "scenes/nfc_blank_card_scene.h"

#include <furi.h>

struct NFCBlankCardApp* nfc_blank_card_app_alloc(void) {
    nfc_blank_card_assert_scene_handlers_correct();

    struct NFCBlankCardApp* instance = malloc(sizeof(*instance));

    instance->scene_manager =
        scene_manager_alloc(&nfc_blank_card_scene_manager_handlers, instance);
    instance->view_dispatcher = view_dispatcher_alloc();

    instance->submenu = submenu_alloc();

    return instance;
}

void nfc_blank_card_app_free(struct NFCBlankCardApp* instance) {
    furi_assert(instance);

    submenu_free(instance->submenu);

    view_dispatcher_free(instance->view_dispatcher);
    scene_manager_free(instance->scene_manager);

    free(instance);
}
