#pragma once

#include <nfc/nfc_device.h>

typedef const char* MfClassicDeviceError;

MfClassicDeviceError mf_classic_blank_device_resettable(NfcDevice* device);
MfClassicDeviceError mf_classic_blank_device_writable(NfcDevice* device);
