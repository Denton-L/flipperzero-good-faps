#pragma once

#include <nfc/nfc.h>

struct MfClassicBlankPoller;

enum MfClassicBlankPollerEvent {
    MfClassicBlankPollerEventTypeDetected,
    MfClassicBlankPollerEventTypeDetectedInvalid, // TODO
    MfClassicBlankPollerEventTypeNotDetected,
};

typedef void (*MfClassicBlankPollerCallback)(void* context, enum MfClassicBlankPollerEvent event);

struct MfClassicBlankPoller* mf_classic_blank_poller_alloc(Nfc* nfc);
void mf_classic_blank_poller_free(struct MfClassicBlankPoller* instance);
void mf_classic_blank_poller_start(struct MfClassicBlankPoller* instance, MfClassicBlankPollerCallback callback, void* context);
void mf_classic_blank_poller_stop(struct MfClassicBlankPoller* instance);
