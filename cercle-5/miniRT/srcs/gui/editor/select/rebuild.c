/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 11:20:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	rebuild_bvh(t_gui *gui)
{
    if (gui->scene->bvh)
        bvh_destroy(gui->scene->bvh);
    gui->scene->bvh = bvh_create(gui->scene);
}
