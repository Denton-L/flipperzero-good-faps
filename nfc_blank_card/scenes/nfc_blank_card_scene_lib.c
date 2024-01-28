#include "nfc_blank_card_scene_lib.h"

void submenu_add_items(Submenu* submenu, void* callback_context, const struct SubmenuItem* items) {
    uint32_t index = 0;
    for (const struct SubmenuItem* item = items; item->label; item++) {
        submenu_add_item(submenu, item->label, index++, item->callback, callback_context);
    }
}
