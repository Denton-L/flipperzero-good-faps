#pragma once

#include <gui/modules/submenu.h>

enum NFCBlankCardAppScene {
    NFCBlankCardAppSceneStart,
};

// TODO: do we move thse into scene_start?
struct SubmenuScene {
    const char* label;
    uint32_t scene_id;
};

void submenu_add_scenes(
    Submenu* submenu,
    SubmenuItemCallback callback,
    void* callback_context,
    const struct SubmenuScene* scenes);
