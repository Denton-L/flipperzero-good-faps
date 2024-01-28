#include "nfc_blank_card_scene_lib.h"

void submenu_add_scenes(
    Submenu* submenu,
    SubmenuItemCallback callback,
    void* callback_context,
    const struct SubmenuScene* scenes) {
    uint32_t index = 0;
    for(const struct SubmenuScene* scene = scenes; scene->label; scene++) {
        submenu_add_item(submenu, scene->label, index++, callback, callback_context);
    }
}
