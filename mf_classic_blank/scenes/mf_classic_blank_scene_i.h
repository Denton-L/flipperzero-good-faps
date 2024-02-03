#pragma once

enum MfClassicBlankAppScene {
#define ADD_SCENE(name, id) MfClassicBlankAppScene##id,
#include "mf_classic_blank_scene_config.h"
#undef ADD_SCENE
};
