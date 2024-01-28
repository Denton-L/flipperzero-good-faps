#pragma once

#include <gui/modules/submenu.h>

enum NFCBlankCardAppScene {
    NFCBlankCardAppSceneStart,
};

struct SubmenuItem {
    const char* label;
    SubmenuItemCallback callback;
};

void submenu_add_items(Submenu* submenu, void* callback_context, const struct SubmenuItem* items);
