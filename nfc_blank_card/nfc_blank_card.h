#pragma once

#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>

struct NFCBlankCardApp {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
};

struct NFCBlankCardApp* nfc_blank_card_app_alloc(void);
void nfc_blank_card_app_free(struct NFCBlankCardApp* instance);