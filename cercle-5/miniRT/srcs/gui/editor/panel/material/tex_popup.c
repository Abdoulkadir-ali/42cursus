/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_popup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 21:26:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include <libgen.h>
#include <stdio.h>

/*
** tex_apply_from_path: loads a texture directly from a path string.
** Sets tex_status 1 (ok) or 2 (fail) and tex_status_msg.
*/
void	tex_apply_from_path(t_gui *gui, const char *path)
{
	t_index		id;
	t_material	*mat;
	char		path_copy[WIDGET_INPUT_BUF_SIZE];
	char		*base;

	if (!path || path[0] == '\0')
		return ;
	id = scene_add_fresh_material(gui->scene, vec3(255, 255, 255));
	if (id.error)
	{
		gui->tex_status = 2;
		ft_strlcpy(gui->tex_status_msg, "Error: no material slot", 64);
		return ;
	}
	mat = &gui->scene->materials[id.i];
	if (!load_texture(gui->win.mlx, &mat->albedo_map, path))
	{
		gui->tex_status = 2;
		ft_strlcpy(gui->tex_status_msg, "Failed to load texture", 64);
		return ;
	}
	set_selected_tex_slot(gui, id.i);
	set_selected_group_slot(gui, 3);
	scene_init_uv_flags(gui->scene);
	ft_strlcpy(path_copy, path, WIDGET_INPUT_BUF_SIZE);
	base = basename(path_copy);
	gui->tex_status = 1;
	snprintf(gui->tex_status_msg, 64, "Loaded: %s", base);
	gui->render.dirty = true;
}

/* Legacy callback kept for any existing widget hookups */
void	tex_apply_callback(t_widget *w, t_gui *gui)
{
	if (w->input_buf[0] != '\0')
		tex_apply_from_path(gui, w->input_buf);
}

void	tex_popup_init(t_gui *gui)
{
	gui->tex_popup_input = NULL;
	gui->tex_popup_open = false;
	gui->tex_status = 0;
	gui->tex_status_msg[0] = '\0';
}

void	draw_tex_preview(t_gui *gui, t_vec2i pos, t_vec2s size, t_texture *tex)
{
	t_vec3i			rgb;
	t_vec3			col;
	unsigned int	color;
	int				px;
	int				py;

	py = 0;
	while (py < (int)size.y)
	{
		px = 0;
		while (px < (int)size.x)
		{
			col = sample_texture(tex, (double)px / size.x,
					(double)py / size.y);
			rgb = vec3_to_rgb(col);
			color = ((unsigned int)rgb.x << 16)
				| ((unsigned int)rgb.y << 8)
				| (unsigned int)rgb.z;
			fill_rect_row(gui, vec2i(pos.x + px, pos.y + py), 1, color);
			px++;
		}
		py++;
	}
}
