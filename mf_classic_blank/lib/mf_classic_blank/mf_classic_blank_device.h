#pragma once

#include <nfc/nfc_device.h>
#include <nfc/protocols/mf_classic/mf_classic.h>

typedef const char* MfClassicDeviceError;

bool mf_classic_blank_device_block_writable(
    const MfClassicData* data,
    uint8_t block_num,
    MfClassicKeyType* key_type_out,
    MfClassicAction* action_out);

MfClassicDeviceError mf_classic_blank_device_resettable(NfcDevice* device);
MfClassicDeviceError mf_classic_blank_device_writable(NfcDevice* device);
