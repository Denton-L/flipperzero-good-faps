#include "mf_classic_blank.h"
#include "mf_classic_blank_device.h"

#include <nfc/protocols/mf_classic/mf_classic.h>

static const MfClassicAction mf_classic_blank_device_key_type_to_write[] = {
    [MfClassicKeyTypeA] = MfClassicActionKeyAWrite,
    [MfClassicKeyTypeB] = MfClassicActionKeyBWrite,
};

bool mf_classic_blank_device_block_writable(
    const MfClassicData* data,
    uint8_t block_num,
    MfClassicKeyType* key_type_out,
    MfClassicAction* action_out) {
    uint8_t sector_num = mf_classic_get_sector_by_block(block_num);
    for(MfClassicKeyType key_type = 0;
        key_type < COUNT_OF(mf_classic_blank_device_key_type_to_write);
        ++key_type) {
        MfClassicAction action = mf_classic_blank_device_key_type_to_write[key_type];

        if(mf_classic_is_key_found(data, sector_num, key_type) &&
           // the function is RO on data, the signature is wrong
           mf_classic_is_allowed_access((MfClassicData*)data, block_num, key_type, action)) {
            if(key_type_out) {
                *key_type_out = key_type;
            }
            if(action_out) {
                *action_out = action;
            }
            return true;
        }
    }
    return false;
}

static MfClassicDeviceError mf_classic_blank_device_mifare_classic_check(
    NfcDevice* device,
    const MfClassicData** data_out) {
    if(nfc_device_get_protocol(device) != NFC_PROTOCOL) {
        return "Protocol not supported; only MiFare Classic devices are allowed"; // TODO: spelling?
    }

    const MfClassicData* data = nfc_device_get_data(device, NFC_PROTOCOL);

    uint16_t total_block_num = mf_classic_get_total_block_num(data->type);
    for(uint16_t block_num = 1; block_num < total_block_num; ++block_num) {
        if(!mf_classic_blank_device_block_writable(data, block_num, NULL, NULL)) {
            return "Unwritable blocks found; keys may be missing or blocks may be write-restricted";
        }
    }

    *data_out = data;
    return NULL;
}

MfClassicDeviceError mf_classic_blank_device_resettable(NfcDevice* device) {
    const MfClassicData* data;
    const char* error = mf_classic_blank_device_mifare_classic_check(device, &data);
    if(error) {
        return error;
    }
    return false;
}

MfClassicDeviceError mf_classic_blank_device_writable(NfcDevice* device) {
    const MfClassicData* data;
    const char* error = mf_classic_blank_device_mifare_classic_check(device, &data);
    if(error) {
        return error;
    }

    if(!mf_classic_is_card_read(data)) {
        return "Device not fully read; ensure all sectors and keys are found";
    }
    return false;
}
