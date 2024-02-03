#pragma once

#include "lib/mf_classic_blank/mf_classic_blank_poller.h"

#include <gui/gui.h>
#include <gui/modules/popup.h>
#include <gui/modules/submenu.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <nfc/nfc_device.h>
#include <notification/notification.h>

enum MfClassicBlankAppView {
    MfClassicBlankAppViewSubmenu,
    MfClassicBlankAppViewPopup,
};

struct MfClassicBlankApp {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    Gui* gui;
    NotificationApp* notification_app;

    Submenu* submenu;
    Popup* popup;

    Nfc* nfc;
    struct MfClassicBlankPoller* mf_classic_blank_poller;

    NfcDevice* nfc_device;
};

struct MfClassicBlankApp* mf_classic_blank_app_alloc(void);
void mf_classic_blank_app_free(struct MfClassicBlankApp* instance);

void mf_classic_blank_app_blink_start(struct MfClassicBlankApp* instance);
void mf_classic_blank_app_blink_stop(struct MfClassicBlankApp* instance);
