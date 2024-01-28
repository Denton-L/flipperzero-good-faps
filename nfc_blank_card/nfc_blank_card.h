#pragma once

#include <gui/modules/submenu.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>

enum NFCBlankCardAppView {
    NFCBlankCardAppViewSubmenu,
};

struct NFCBlankCardApp {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    Gui* gui;

    Submenu* submenu;
};

struct NFCBlankCardApp* nfc_blank_card_app_alloc(void);
void nfc_blank_card_app_free(struct NFCBlankCardApp* instance);
