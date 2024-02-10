#include "mf_classic_blank_scene_lib.h"

#include <mf_classic_blank_icons.h>

void show_message(Widget* widget, const char* title, const char* body) {
    widget_add_string_element(
        widget, 1, 4, AlignLeft, AlignTop, FontPrimary, title);
    widget_add_string_multiline_element(
        widget,
        1,
        17,
        AlignLeft,
        AlignTop,
        FontSecondary,
        body);
}
