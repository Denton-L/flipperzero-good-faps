#pragma once

enum NFCBlankCardAppScene {
#define ADD_SCENE(name, id) NFCBlankCardAppScene##id,
#include "nfc_blank_card_scene_config.h"
#undef ADD_SCENE
};
