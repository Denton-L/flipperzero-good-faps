#pragma once

#include <nfc/nfc.h>

struct NfcBlankCardPoller;

enum NfcBlankCardPollerEvent {
    NfcBlankCardPollerEventTypeDetected,
    NfcBlankCardPollerEventTypeDetectedInvalid, // TODO
    NfcBlankCardPollerEventTypeNotDetected,
};

typedef void (*NfcBlankCardPollerCallback)(void* context, enum NfcBlankCardPollerEvent event);

struct NfcBlankCardPoller* nfc_blank_card_poller_alloc(Nfc* nfc);
void nfc_blank_card_poller_free(struct NfcBlankCardPoller* instance);
void nfc_blank_card_poller_start(struct NfcBlankCardPoller* instance, NfcBlankCardPollerCallback callback, void* context);
void nfc_blank_card_poller_stop(struct NfcBlankCardPoller* instance);
