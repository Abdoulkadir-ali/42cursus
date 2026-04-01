#include "functions/gui/render.h"
#include "functions/gui/window.h"
#include "mlx.h"
#include <stdio.h>

const char *mesh_name(t_mesh *mesh)
{
	if (mesh->name)
		return (mesh->name);
	return ("(unnamed)");
}

void draw_ui_help(t_gui *gui, int *y)
{
	int ox = 220 + 16; // SCENE_PANEL_W
	mlx_string_put(gui->win.mlx, gui->win.win, ox, *y, 0xE0A820, "miniRT");
	*y += 24;
	mlx_string_put(gui->win.mlx, gui->win.win, ox, *y, 0xD0D0D8, "WASD  Move   SPACE/SHIFT  Up/Down");
	*y += 20;
	mlx_string_put(gui->win.mlx, gui->win.win, ox, *y, 0xD0D0D8, "LMB   Look   MMB  Zoom");
	*y += 20;
	mlx_string_put(gui->win.mlx, gui->win.win, ox, *y, 0xD0D0D8, "+/-   Speed  N/P  Maps  X  Physics");
	*y += 20;
}

void draw_ui_status(t_gui *gui, int *y)
{
	int ox = 220 + 16;
	int color;
	char buf[64];

	if (gui->physics_enabled)
	{
		color = 0x44FF44;
		snprintf(buf, sizeof(buf), "[ X ]  PHYSICS  ON");
	}
	else
	{
		color = 0xFF4444;
		snprintf(buf, sizeof(buf), "[   ]  PHYSICS  OFF");
	}
	mlx_string_put(gui->win.mlx, gui->win.win, ox, *y, color, buf);
	*y += 20;
}

void draw_ui_object(t_gui *gui)
{
	char buf[128];
	t_mesh *mesh;

	if (!gui || !gui->scene || gui->scene->mesh_count == 0)
		return ;
	mesh = &gui->scene->meshes[0];
	snprintf(buf, sizeof(buf), "Object: %s", mesh_name(mesh));
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 38, 0xE0A820, buf);
	snprintf(buf, sizeof(buf), "Material: %d", mesh->mat_id);
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 58, 0xD0D0D8, buf);
	snprintf(buf, sizeof(buf), "Vertices: %d", mesh->vertex_count);
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 78, 0xD0D0D8, buf);
	snprintf(buf, sizeof(buf), "Transform: Pos(%.2f,%.2f,%.2f)",
mesh->transform.pos.x, mesh->transform.pos.y, mesh->transform.pos.z);
	mlx_string_put(gui->win.mlx, gui->win.win, 350, 98, 0xD0D0D8, buf);
}
