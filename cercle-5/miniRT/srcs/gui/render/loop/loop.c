#include "functions/gui/window.h"
#include "functions/gui/input.h"
#include <X11/X.h>

int gui_update(t_gui *gui);

void gui_loop(t_gui *gui)
{
	mlx_hook(gui->win.win, KeyPress, (1L << 0), key_press, gui);
	mlx_hook(gui->win.win, KeyRelease, (1L << 1), key_release, gui);
	mlx_hook(gui->win.win, ButtonPress, (1L << 2), mouse_click_hook(), gui);
	mlx_hook(gui->win.win, ButtonRelease, (1L << 3), mouse_release_hook(), gui);
	mlx_hook(gui->win.win, MotionNotify, (1L << 6), mouse_motion_hook(), gui);
	mlx_hook(gui->win.win, DestroyNotify, 0, gui_window_close, gui);
	mlx_loop_hook(gui->win.mlx, (int (*)(void *))gui_update, gui);
	mlx_loop(gui->win.mlx);
}
