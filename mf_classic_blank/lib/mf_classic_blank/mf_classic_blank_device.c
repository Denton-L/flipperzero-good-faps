#include "mf_classic_blank.h"
#include "mf_classic_blank_device.h"

#include <nfc/protocols/mf_classic/mf_classic.h>

static MfClassicDeviceError mf_classic_blank_device_mifare_classic_check(NfcDevice* device) {
    if (nfc_device_get_protocol(device) != NFC_PROTOCOL) {
        return "Protocol not supported; only Mifare Classic devices are allowed";
    }

    const MfClassicData* data = nfc_device_get_data(device, NFC_PROTOCOL);

    UNUSED(data);

    return NULL;
}

MfClassicDeviceError mf_classic_blank_device_resettable(NfcDevice* device) {
    const char* error = mf_classic_blank_device_mifare_classic_check(device);
    if (error) {
        return error;
    }
    return false;
}

MfClassicDeviceError mf_classic_blank_device_writable(NfcDevice* device) {
    const char* error = mf_classic_blank_device_mifare_classic_check(device);
    if (error) {
        return error;
    }
    return false;
}
