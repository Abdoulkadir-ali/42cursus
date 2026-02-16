/* Example: Add a physics checkbox widget at startup in gui_init */
#include "gui.h"
#include <stdlib.h>

void widget_physics_toggle(t_widget *w, t_gui *gui) {
    gui->physics_enabled = !gui->physics_enabled;
    w->value = gui->physics_enabled;
    gui->render.dirty = true;
}

void widget_init_default(t_gui *gui) {
    t_widget *cb = widget_create(WIDGET_CHECKBOX, 32, 122, 180, 20, "Simulate Physics");
    cb->value = gui->physics_enabled;
    cb->on_click = widget_physics_toggle;
    widget_add(gui, cb);
}
