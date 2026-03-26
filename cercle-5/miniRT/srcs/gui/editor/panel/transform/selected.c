/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selected.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
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
    if (sel->type == TYPE_RECT)
        return (&sc->rects[sel->index].transform);
    if (sel->type == TYPE_PYRAMID)
        return (&sc->pyramids[sel->index].transform);
    if (sel->type == TYPE_BOX)
        return (&sc->boxes[sel->index].transform);
    if (sel->type == TYPE_CAPSULE)
        return (&sc->capsules[sel->index].transform);
    if (sel->type == TYPE_TRI)
        return (&sc->tris[sel->index].transform);
    if (sel->type == TYPE_MESH)
        return (&sc->groups[sel->index].transform);
    return (NULL);
}
