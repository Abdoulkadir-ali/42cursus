/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_popup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include <libgen.h>
#include <stdio.h>

static void	tex_load_err(t_gui *gui, const char *msg)
{
	gui->tex_status = 2;
	ft_strlcpy(gui->tex_status_msg, msg, 64);
}

void	tex_apply_from_path(t_gui *gui, const char *path)
{
	t_index		id;
	t_material	*mat;
	char		p_copy[WIDGET_INPUT_BUF_SIZE];

	if (!path || path[0] == '\0')
		return ;
	id = scene_add_fresh_material(gui->scene, vec3(255, 255, 255));
	if (id.error)
		return (tex_load_err(gui, "Error: no material slot"));
	mat = &gui->scene->materials[id.i];
	if (!load_texture(gui->win.mlx, &mat->albedo_map, path))
		return (tex_load_err(gui, "Failed to load texture"));
	set_selected_tex_slot(gui, id.i);
	set_selected_group_slot(gui, 3);
	scene_init_uv_flags(gui->scene);
	ft_strlcpy(p_copy, path, WIDGET_INPUT_BUF_SIZE);
	gui->tex_status = 1;
	snprintf(gui->tex_status_msg, 64, "Loaded: %s", basename(p_copy));
	gui->render.dirty = true;
}

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
	unsigned int	color;
	int				px;
	int				py;

	py = 0;
	while (py < (int)size.y)
	{
		px = 0;
		while (px < (int)size.x)
		{
			rgb = vec3_to_rgb(sample_texture(tex, (double)px / size.x,
						(double)py / size.y));
			color = ((unsigned int)rgb.x << 16) | ((unsigned int)rgb.y << 8)
				| (unsigned int)rgb.z;
			fill_rect_row(gui, vec2i(pos.x + px, pos.y + py), 1, color);
			px++;
		}
		py++;
	}
}
