#pragma once

#include <gui/modules/widget.h>

enum MfClassicBlankAppScene {
#define ADD_SCENE(name, id) MfClassicBlankAppScene##id,
#include "mf_classic_blank_scene_config.h"
#undef ADD_SCENE
};

void show_message(Widget* widget, const char* title, const char* body);
