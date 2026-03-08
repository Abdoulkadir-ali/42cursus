/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 06:22:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"
#include <unistd.h>

/* ── helpers ──────────────────────────────────────────────────────────────── */

static bool	phit(t_vec2i m, int x, int y, int w, int h)
{
	return (m.x >= x && m.x < x + w && m.y >= y && m.y < y + h);
}

/* Draw a centred modal box; returns its top-left x/y in *ox, *oy. */
static void	draw_modal_bg(t_gui *gui, int h, int *ox, int *oy)
{
	t_panel	dim;
	t_panel	box;

	/* Full-screen dim */
	dim = (t_panel){.x = 0, .y = 0,
		.w = gui->win.disp_w, .h = gui->win.disp_h,
		.bg = 0x0D0D14, .brd = 0x0D0D14,
		.pos = vec2i(0, 0), .size = vec2i(gui->win.disp_w, gui->win.disp_h)};
	draw_panel(gui, dim);
	*ox = (gui->win.disp_w - POPUP_W) / 2;
	*oy = (gui->win.disp_h - h) / 2;
	/* Modal box */
	box = (t_panel){.x = *ox, .y = *oy, .w = POPUP_W, .h = h,
		.bg = 0x1A1A28, .brd = COL_ACCENT,
		.pos = vec2i(*ox, *oy), .size = vec2i(POPUP_W, h)};
	draw_panel(gui, box);
}

static void	draw_popup_btn(t_gui *gui, int x, int y, int w, int h,
	const char *lbl, int bg)
{
	t_panel	btn;

	btn = (t_panel){.x = x, .y = y, .w = w, .h = h,
		.bg = bg, .brd = COL_BORDER,
		.pos = vec2i(x, y), .size = vec2i(w, h)};
	draw_panel(gui, btn);
	mlx_string_put(gui->win.mlx, gui->win.win,
		x + 8, y + h / 2, COL_TEXT, (char *)lbl);
}

/* ── Step 1: shape picker ─────────────────────────────────────────────────── */

static void	dispatch_shape(t_gui *gui, int i)
{
	if (i == 0)
		editor_add_sphere(gui);
	else if (i == 1)
		editor_add_plane(gui);
	else if (i == 2)
		editor_add_cylinder(gui);
	else if (i == 3)
		editor_add_cone(gui);
	else if (i == 4)
		editor_add_light(gui);
	else if (i == 5)
		editor_add_tri(gui);
	else if (i == 6)
		editor_add_rect(gui);
	else if (i == 7)
		editor_add_pyramid(gui);
	gui->crud.popup = POPUP_NONE;
	gui->render.dirty = true;
}

static void	draw_popup_shape(t_gui *gui)
{
	static const char	*labels[9] = {
		"Sphere", "Plane", "Cylinder",
		"Cone", "Light", "Triangle",
		"Rectangle", "Pyramid", "Mesh  \xe2\x86\x92"
	};
	int					ox;
	int					oy;
	int					bw;
	int					bh;
	int					bg;
	int					i;

	draw_modal_bg(gui, POPUP_PAD * 2 + 36 + 3 * (POPUP_ITEM_H + 8) + 40,
		&ox, &oy);
	mlx_string_put(gui->win.mlx, gui->win.win,
		ox + POPUP_PAD, oy + POPUP_PAD, COL_ACCENT, "Add Object");
	bw = (POPUP_W - POPUP_PAD * 4) / 3;
	bh = POPUP_ITEM_H;
	i = 0;
	while (i < 9)
	{
		bg = 0x22222E;
		if (i == 8)
			bg = 0x1E2A1E;
		draw_popup_btn(gui,
			ox + POPUP_PAD + (i % 3) * (bw + POPUP_PAD),
			oy + 36 + POPUP_PAD + (i / 3) * (bh + 8),
			bw, bh, labels[i], bg);
		i++;
	}
	draw_popup_btn(gui, ox + POPUP_W - 90 - POPUP_PAD,
		oy + 36 + POPUP_PAD + 3 * (bh + 8) + 4,
		90, 26, "Cancel", 0x2A1A1A);
}

static bool	click_popup_shape(t_gui *gui, t_vec2i mouse)
{
	int	ox;
	int	oy;
	int	bw;
	int	bh;
	int	i;
	int	modal_h;

	bw = (POPUP_W - POPUP_PAD * 4) / 3;
	bh = POPUP_ITEM_H;
	modal_h = POPUP_PAD * 2 + 36 + 3 * (POPUP_ITEM_H + 8) + 40;
	ox = (gui->win.disp_w - POPUP_W) / 2;
	oy = (gui->win.disp_h - modal_h) / 2;
	i = 0;
	while (i < 9)
	{
		if (phit(mouse,
				ox + POPUP_PAD + (i % 3) * (bw + POPUP_PAD),
				oy + 36 + POPUP_PAD + (i / 3) * (bh + 8), bw, bh))
		{
			if (i == 8)
			{
				gui->crud.popup = POPUP_MESH_FMT;
				gui->render.dirty = true;
				return (true);
			}
			dispatch_shape(gui, i);
			return (true);
		}
		i++;
	}
	if (phit(mouse, ox + POPUP_W - 90 - POPUP_PAD,
			oy + 36 + POPUP_PAD + 3 * (bh + 8) + 4, 90, 26))
		gui->crud.popup = POPUP_NONE;
	gui->render.dirty = true;
	return (true);
}

/* ── Step 2: mesh format picker ───────────────────────────────────────────── */

static void	draw_popup_mesh_fmt(t_gui *gui)
{
	int	ox;
	int	oy;
	int	bw;
	int	modal_h;

	modal_h = POPUP_PAD * 2 + 36 + POPUP_ITEM_H + 16 + 36;
	draw_modal_bg(gui, modal_h, &ox, &oy);
	mlx_string_put(gui->win.mlx, gui->win.win,
		ox + POPUP_PAD, oy + POPUP_PAD, COL_ACCENT, "Add Mesh \xe2\x80\x94 Format");
	bw = (POPUP_W - POPUP_PAD * 3) / 2;
	draw_popup_btn(gui, ox + POPUP_PAD,
		oy + 36 + POPUP_PAD, bw, POPUP_ITEM_H, "OBJ", 0x22222E);
	draw_popup_btn(gui, ox + POPUP_PAD * 2 + bw,
		oy + 36 + POPUP_PAD, bw, POPUP_ITEM_H, "GLB", 0x22222E);
	draw_popup_btn(gui, ox + POPUP_PAD,
		oy + modal_h - 36, 80, 26, "\xe2\x86\x90 Back", 0x22222E);
	draw_popup_btn(gui, ox + POPUP_W - 90 - POPUP_PAD,
		oy + modal_h - 36, 90, 26, "Cancel", 0x2A1A1A);
}

static bool	click_popup_mesh_fmt(t_gui *gui, t_vec2i mouse)
{
	int	ox;
	int	oy;
	int	bw;
	int	modal_h;

	modal_h = POPUP_PAD * 2 + 36 + POPUP_ITEM_H + 16 + 36;
	ox = (gui->win.disp_w - POPUP_W) / 2;
	oy = (gui->win.disp_h - modal_h) / 2;
	bw = (POPUP_W - POPUP_PAD * 3) / 2;
	if (phit(mouse, ox + POPUP_PAD, oy + 36 + POPUP_PAD, bw, POPUP_ITEM_H))
	{
		gui->crud.mesh_fmt = MESH_FMT_OBJ;
		gui->crud.popup = POPUP_MESH_PATH;
		gui->crud.path_buf[0] = '\0';
		gui->crud.path_len = 0;
		gui->crud.path_error = false;
		gui->render.dirty = true;
		return (true);
	}
	if (phit(mouse, ox + POPUP_PAD * 2 + bw, oy + 36 + POPUP_PAD,
			bw, POPUP_ITEM_H))
	{
		gui->crud.mesh_fmt = MESH_FMT_GLB;
		gui->crud.popup = POPUP_MESH_PATH;
		gui->crud.path_buf[0] = '\0';
		gui->crud.path_len = 0;
		gui->crud.path_error = false;
		gui->render.dirty = true;
		return (true);
	}
	if (phit(mouse, ox + POPUP_PAD, oy + modal_h - 36, 80, 26))
		gui->crud.popup = POPUP_SHAPE;
	else
		gui->crud.popup = POPUP_NONE;
	gui->render.dirty = true;
	return (true);
}

/* ── Step 3: path input ───────────────────────────────────────────────────── */

void	popup_load_mesh(t_gui *gui)
{
	if (gui->crud.path_len == 0)
	{
		gui->crud.path_error = true;
		gui->render.dirty = true;
		return ;
	}
	if (access(gui->crud.path_buf, R_OK) != 0)
	{
		gui->crud.path_error = true;
		gui->render.dirty = true;
		return ;
	}
	if (gui->crud.mesh_fmt == MESH_FMT_OBJ)
		editor_add_obj(gui, gui->crud.path_buf);
	else
		editor_add_glb(gui, gui->crud.path_buf);
	gui->crud.popup = POPUP_NONE;
	gui->crud.path_error = false;
	gui->render.dirty = true;
}

static void	draw_popup_mesh_path(t_gui *gui)
{
	char	display[64];
	int		ox;
	int		oy;
	int		modal_h;
	int		field_y;
	int		err_col;

	modal_h = POPUP_PAD * 2 + 36 + 36 + POPUP_ITEM_H + 16 + 36;
	draw_modal_bg(gui, modal_h, &ox, &oy);
	if (gui->crud.mesh_fmt == MESH_FMT_OBJ)
		mlx_string_put(gui->win.mlx, gui->win.win,
			ox + POPUP_PAD, oy + POPUP_PAD,
			COL_ACCENT, "Add Mesh \xe2\x80\x94 Path (OBJ)");
	else
		mlx_string_put(gui->win.mlx, gui->win.win,
			ox + POPUP_PAD, oy + POPUP_PAD,
			COL_ACCENT, "Add Mesh \xe2\x80\x94 Path (GLB)");
	field_y = oy + 36 + POPUP_PAD + 24;
	err_col = gui->crud.path_error ? 0xFF4444 : COL_BORDER;
	t_panel field = {.x = ox + POPUP_PAD, .y = field_y,
		.w = POPUP_W - POPUP_PAD * 2, .h = POPUP_ITEM_H,
		.bg = 0x0D0D14, .brd = err_col,
		.pos = vec2i(ox + POPUP_PAD, field_y),
		.size = vec2i(POPUP_W - POPUP_PAD * 2, POPUP_ITEM_H)};
	draw_panel(gui, field);
	/* show up to last 40 chars if path is long */
	if (gui->crud.path_len <= 40)
		snprintf(display, sizeof(display), "> %s_", gui->crud.path_buf);
	else
		snprintf(display, sizeof(display), "> ...%s_",
			gui->crud.path_buf + gui->crud.path_len - 37);
	mlx_string_put(gui->win.mlx, gui->win.win,
		ox + POPUP_PAD + 6, field_y + POPUP_ITEM_H / 2,
		gui->crud.path_error ? 0xFF6666 : COL_TEXT, display);
	if (gui->crud.path_error)
		mlx_string_put(gui->win.mlx, gui->win.win,
			ox + POPUP_PAD, field_y + POPUP_ITEM_H + 6,
			0xFF4444, "File not found");
	draw_popup_btn(gui, ox + POPUP_PAD, oy + modal_h - 36, 80, 26,
		"\xe2\x86\x90 Back", 0x22222E);
	draw_popup_btn(gui, ox + (POPUP_W - 70) / 2, oy + modal_h - 36, 70, 26,
		"Load", 0x1A2A1A);
	draw_popup_btn(gui, ox + POPUP_W - 90 - POPUP_PAD, oy + modal_h - 36,
		90, 26, "Cancel", 0x2A1A1A);
}

static bool	click_popup_mesh_path(t_gui *gui, t_vec2i mouse)
{
	int	ox;
	int	oy;
	int	modal_h;

	modal_h = POPUP_PAD * 2 + 36 + 36 + POPUP_ITEM_H + 16 + 36;
	ox = (gui->win.disp_w - POPUP_W) / 2;
	oy = (gui->win.disp_h - modal_h) / 2;
	if (phit(mouse, ox + POPUP_PAD, oy + modal_h - 36, 80, 26))
	{
		gui->crud.popup = POPUP_MESH_FMT;
		gui->crud.path_error = false;
		gui->render.dirty = true;
		return (true);
	}
	if (phit(mouse, ox + (POPUP_W - 70) / 2, oy + modal_h - 36, 70, 26))
	{
		popup_load_mesh(gui);
		return (true);
	}
	gui->crud.popup = POPUP_NONE;
	gui->crud.path_error = false;
	gui->render.dirty = true;
	return (true);
}

/* ── Public interface ─────────────────────────────────────────────────────── */

void	draw_popup(t_gui *gui)
{
	if (gui->crud.popup == POPUP_SHAPE)
		draw_popup_shape(gui);
	else if (gui->crud.popup == POPUP_MESH_FMT)
		draw_popup_mesh_fmt(gui);
	else if (gui->crud.popup == POPUP_MESH_PATH)
		draw_popup_mesh_path(gui);
}

bool	popup_handle_click(t_gui *gui, t_vec2i mouse)
{
	if (gui->crud.popup == POPUP_NONE)
		return (false);
	if (gui->crud.popup == POPUP_SHAPE)
		return (click_popup_shape(gui, mouse));
	if (gui->crud.popup == POPUP_MESH_FMT)
		return (click_popup_mesh_fmt(gui, mouse));
	if (gui->crud.popup == POPUP_MESH_PATH)
		return (click_popup_mesh_path(gui, mouse));
	return (false);
}

/*
** Map an unshifted keysym to its Shift-level character.
** MLX always delivers level-0 (unshifted) keysyms, so we do this ourselves.
** Covers lowercase→uppercase and the AZERTY symbols needed in file paths.
*/
static char	popup_shift_char(int keycode)
{
	/* a-z → A-Z */
	if (keycode >= 'a' && keycode <= 'z')
		return ((char)(keycode - 32));
	/* AZERTY-specific shifted symbols useful in file paths */
	if (keycode == ':')  return ('/');   /* Maj+: → /  (AZERTY bottom row) */
	if (keycode == ';')  return ('.');   /* Maj+; → .  (AZERTY bottom row) */
	if (keycode == '.')  return ('>');
	if (keycode == ',')  return ('<');
	if (keycode == '-')  return ('_');   /* hyphen → underscore */
	if (keycode == '1')  return ('!');
	if (keycode == '2')  return ('@');
	if (keycode == '3')  return ('#');
	if (keycode == '4')  return ('$');
	if (keycode == '5')  return ('%');
	if (keycode == '6')  return ('^');
	if (keycode == '7')  return ('&');
	if (keycode == '8')  return ('*');
	if (keycode == '9')  return ('(');
	if (keycode == '0')  return (')');
	/* Already uppercase or non-remapped — echo as-is */
	return ((char)keycode);
}

bool	popup_handle_key(t_gui *gui, int keycode)
{
	if (gui->crud.popup != POPUP_MESH_PATH)
		return (false);
	if (keycode == XK_Escape)
	{
		gui->crud.popup = POPUP_NONE;
		gui->crud.path_error = false;
		gui->render.dirty = true;
		return (true);
	}
	if (keycode == XK_Return)
	{
		popup_load_mesh(gui);
		return (true);
	}
	if (keycode == XK_BackSpace)
	{
		if (gui->crud.path_len > 0)
			gui->crud.path_buf[--gui->crud.path_len] = '\0';
		gui->crud.path_error = false;
		gui->render.dirty = true;
		return (true);
	}
	/* Resolve the character to append, accounting for Shift (MLX always
	** delivers the unshifted/level-0 keysym regardless of modifier state). */
	if (keycode >= 32 && keycode <= 126
		&& gui->crud.path_len < (int)(sizeof(gui->crud.path_buf) - 1))
	{
		char	ch;

		if (gui->crud.shift_held)
			ch = popup_shift_char(keycode);
		else
			ch = (char)keycode;
		if (ch)
		{
			gui->crud.path_buf[gui->crud.path_len++] = ch;
			gui->crud.path_buf[gui->crud.path_len] = '\0';
			gui->crud.path_error = false;
			gui->render.dirty = true;
		}
		return (true);
	}
	return (true);
}

