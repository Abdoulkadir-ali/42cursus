/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:55:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
static void	draw_info_row(t_gui *gui, t_vec2i pos, const char *label,
        const char *val)
{
    mlx_string_put(gui->win.mlx, gui->win.win, pos.x + 8, pos.y, COL_HOVER,
        (char *)label);
    mlx_string_put(gui->win.mlx, gui->win.win, pos.x + 96, pos.y, COL_TEXT,
        (char *)val);
}

void	draw_mesh_info_panel(t_gui *gui, int x)
{
    t_mesh_group	*g;
    t_mesh		*mesh;
    char		buf[64];
    int			y;

    if (!gui->scene || gui->selection->index >= gui->scene->group_count)
        return ;
    g = &gui->scene->groups[gui->selection->index];
    mesh = &gui->scene->meshes[g->start];
    mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 88, COL_HOVER,
        "MESH INFO");
    y = 106;
    if (g->name)
        snprintf(buf, sizeof(buf), "%.24s", g->name);
    else
        snprintf(buf, sizeof(buf), "(unnamed)");
    draw_info_row(gui, vec2i(x, y), "Name:", buf);
    y += 18;
    snprintf(buf, sizeof(buf), "%d", g->sub_count);
    draw_info_row(gui, vec2i(x, y), "Sub-meshes:", buf);
    y += 18;
    snprintf(buf, sizeof(buf), "%d", mesh->vertex_count);
    draw_info_row(gui, vec2i(x, y), "Vertices[0]:", buf);
    y += 18;
    snprintf(buf, sizeof(buf), "%d", mesh->tri_count);
    draw_info_row(gui, vec2i(x, y), "Triangles[0]:", buf);
    y += 18;
    snprintf(buf, sizeof(buf), "%d", g->anim_clip_count);
    draw_info_row(gui, vec2i(x, y), "Animations:", buf);
    y += 18;
    snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f", mesh->bbox.min.x,
        mesh->bbox.min.y, mesh->bbox.min.z);
    draw_info_row(gui, vec2i(x, y), "BBox min:", buf);
    y += 18;
    snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f", mesh->bbox.max.x,
        mesh->bbox.max.y, mesh->bbox.max.z);
    draw_info_row(gui, vec2i(x, y), "BBox max:", buf);
}
