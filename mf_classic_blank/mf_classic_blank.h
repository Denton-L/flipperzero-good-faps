#pragma once

#include "lib/mf_classic_blank/mf_classic_blank_device.h"
#include "lib/mf_classic_blank/mf_classic_blank_poller.h"

#include <dialogs/dialogs.h>
#include <gui/gui.h>
#include <gui/modules/popup.h>
#include <gui/modules/submenu.h>
#include <gui/modules/widget.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <nfc/nfc_device.h>
#include <notification/notification.h>
#include <storage/storage.h>

#define NFC_APP_FOLDER ANY_PATH("nfc")

struct MfClassicBlankAppMode {
    const char* label;
    MfClassicDeviceError (*device_check)(NfcDevice* device);
};

extern const struct MfClassicBlankAppMode mf_classic_blank_app_modes[];

enum MfClassicBlankAppView {
    MfClassicBlankAppViewSubmenu,
    MfClassicBlankAppViewPopup,
    MfClassicBlankAppViewWidget,
};

struct MfClassicBlankApp {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    DialogsApp* dialogs_app;
    Gui* gui;
    NotificationApp* notification_app;
    Storage* storage;

    Submenu* submenu;
    Popup* popup;
    Widget* widget;

    const struct MfClassicBlankAppMode* mode;
    const char* error;

    FuriString* file_path;
    NfcDevice* source_nfc_device;

    Nfc* nfc;
    struct MfClassicBlankPoller* mf_classic_blank_poller;
};

struct MfClassicBlankApp* mf_classic_blank_app_alloc(void);
void mf_classic_blank_app_free(struct MfClassicBlankApp* instance);

void mf_classic_blank_app_blink_start(struct MfClassicBlankApp* instance);
void mf_classic_blank_app_blink_stop(struct MfClassicBlankApp* instance);
