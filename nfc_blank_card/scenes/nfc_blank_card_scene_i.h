#pragma once

enum NfcBlankCardAppScene {
#define ADD_SCENE(name, id) NfcBlankCardAppScene##id,
#include "nfc_blank_card_scene_config.h"
#undef ADD_SCENE
};
