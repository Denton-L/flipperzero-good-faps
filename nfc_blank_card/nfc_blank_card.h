#pragma once

#include "lib/blank_card/nfc_blank_card_poller.h"

#include <gui/gui.h>
#include <gui/modules/popup.h>
#include <gui/modules/submenu.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <nfc/nfc_device.h>
#include <notification/notification.h>

enum NfcBlankCardAppView {
    NfcBlankCardAppViewSubmenu,
    NfcBlankCardAppViewPopup,
};

struct NfcBlankCardApp {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    Gui* gui;
    NotificationApp* notification_app;

    Submenu* submenu;
    Popup* popup;

    Nfc* nfc;
    struct NfcBlankCardPoller* nfc_blank_card_poller;

    NfcDevice* nfc_device;
};

struct NfcBlankCardApp* nfc_blank_card_app_alloc(void);
void nfc_blank_card_app_free(struct NfcBlankCardApp* instance);

void nfc_blank_card_app_blink_start(struct NfcBlankCardApp* instance);
void nfc_blank_card_app_blink_stop(struct NfcBlankCardApp* instance);
