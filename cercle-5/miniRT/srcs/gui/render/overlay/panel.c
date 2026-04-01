#include "functions/gui/render.h"
#include "functions/gui/window.h"
#include "functions/gui/editor.h"

static void draw_panel_pixel(t_gui *gui, t_panel panel, t_vec2i pos)
{
	int col;
	uint32_t *dst;

	col = panel_color(panel, pos);
	if (col == -1)
		return ;
	dst = (uint32_t *)(gui->win.addr + (pos.y * gui->win.line_len + pos.x * (gui->win.bpp / 8)));
	*dst = color_blend(*dst, col, 0.85f);
}

void draw_panel(t_gui *gui, t_panel panel)
{
	t_vec2i pos;

	pos.y = panel.pos.y;
	while (pos.y < panel.pos.y + panel.size.y)
	{
		pos.x = panel.pos.x;
		while (pos.x < panel.pos.x + panel.size.x)
		{
			draw_panel_pixel(gui, panel, pos);
			pos.x++;
		}
		pos.y++;
	}
}

void draw_ui_panels(t_gui *gui)
{
	draw_scene_panel_bg(gui);
	draw_inspector_bg(gui);
}
