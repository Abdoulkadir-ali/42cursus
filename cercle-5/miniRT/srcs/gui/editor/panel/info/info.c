/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_bbox_info(t_gui *gui, t_mesh *mesh, t_vec2i pos);
void	draw_anim_section(t_gui *gui, t_vec2i pos, t_mesh *mesh);
void	draw_mesh_basic_info(t_gui *gui, t_mesh_group *g, t_mesh *mesh,
			t_vec2i pos);
void	set_mesh_ptr(t_gui *gui, t_mesh_group **g, t_mesh **mesh);

void	draw_mesh_info_panel(t_gui *gui, t_vec2i pos)
{
	t_vec2s			d;
	t_mesh_group	*g;
	t_mesh			*mesh;

	d = gui->win.disp_size;
	g = NULL;
	mesh = NULL;
	if (!gui->scene || gui->selection.index.error)
		return ;
	set_mesh_ptr(gui, &g, &mesh);
	if (!mesh)
		return ;
	mlx_string_put(gui->win.mlx, gui->win.win, pos.x + ui_sx(8, d),
		ui_sy(88, d), COL_HOVER, "MESH INFO");
	draw_mesh_basic_info(gui, g, mesh, pos);
	draw_bbox_info(gui, mesh, pos);
	if (mesh->skeleton && mesh->bone_count > 0)
		draw_anim_section(gui, pos, mesh);
}
