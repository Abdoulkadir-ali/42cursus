#include "functions/gui/render.h"

void gui_render(t_gui *gui)
{
	t_render render;

	if (!gui || !gui->scene)
		return ;
	render.gui = gui;
	render.next_tile_id = 0;
	render.tiles_count.x = (gui->win.size.x + TILE_SIZE - 1) / TILE_SIZE;
	render.tiles_count.y = (gui->win.size.y + TILE_SIZE - 1) / TILE_SIZE;
	render.total_tiles = render.tiles_count.x * render.tiles_count.y;
	render.step = gui->render.scale;
	render.transform = gui->scene->camera.transform;
	render.aspect_ratio = (double)gui->win.size.x / (double)gui->win.size.y;
	render.half_height = tan(gui->scene->camera.fov * 0.5 * 3.14159 / 180.0);
	render.half_width = render.half_height * render.aspect_ratio;
	render_tiles(&render);
}
