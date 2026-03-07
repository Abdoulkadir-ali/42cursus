/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 20:55:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

t_transform	*get_selected_transform(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;

	sel = &gui->selection;
	sc = gui->scene;
	if (!sel->active || !sc)
		return (NULL);
	if (sel->type == TYPE_SPHERE)
		return (&sc->spheres[sel->index].transform);
	if (sel->type == TYPE_PLANE)
		return (&sc->planes[sel->index].transform);
	if (sel->type == TYPE_CYLINDER)
		return (&sc->cylinders[sel->index].transform);
	if (sel->type == TYPE_CONE)
		return (&sc->cones[sel->index].transform);
	if (sel->type == TYPE_MESH)
		return (&sc->meshes[sel->index].transform);
	return (NULL);
}

static void	draw_double_row(t_gui *gui, int x, int y,
	const char *label, double value)
{
	char	buf[64];

	snprintf(buf, sizeof(buf), "  %s %.3f", label, value);
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, y, COL_TEXT, buf);
}

static void	draw_vec3_section(t_gui *gui, int x, int *y,
	const char *sec, t_vec3 *v)
{
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, *y, COL_HOVER,
		(char *)sec);
	*y += 20;
	draw_double_row(gui, x, *y, "X:", v->x);
	*y += 18;
	draw_double_row(gui, x, *y, "Y:", v->y);
	*y += 18;
	draw_double_row(gui, x, *y, "Z:", v->z);
	*y += 24;
}

void	draw_transform_panel(t_gui *gui, int x)
{
	t_transform	*tr;
	t_vec3		rot_deg;
	int			y;

	tr = get_selected_transform(gui);
	if (!tr)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			x + 8, 90, COL_TEXT, "No transform");
		return ;
	}
	y = 90;
	rot_deg = vec3(tr->rotation.pitch * 57.296,
			tr->rotation.yaw * 57.296,
			tr->rotation.roll * 57.296);
	draw_vec3_section(gui, x, &y, "Position", &tr->pos);
	draw_vec3_section(gui, x, &y, "Rotation deg", &rot_deg);
	draw_vec3_section(gui, x, &y, "Scale", &tr->scale);
}
