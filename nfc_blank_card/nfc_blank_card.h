#pragma once

#include <gui/gui.h>
#include <gui/modules/popup.h>
#include <gui/modules/submenu.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <notification/notification.h>
#include <notification/notification_messages.h>

enum NFCBlankCardAppView {
    NFCBlankCardAppViewSubmenu,
    NFCBlankCardAppViewPopup,
};

struct NFCBlankCardApp {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    Gui* gui;
    NotificationApp* notifications;

    Submenu* submenu;
    Popup* popup;
};

struct NFCBlankCardApp* nfc_blank_card_app_alloc(void);
void nfc_blank_card_app_free(struct NFCBlankCardApp* instance);

void nfc_blank_card_app_blink_start(struct NFCBlankCardApp* instance);
void nfc_blank_card_app_blink_stop(struct NFCBlankCardApp* instance);
