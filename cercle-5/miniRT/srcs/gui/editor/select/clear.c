/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:40:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	clear_selection(t_gui *gui)
{
    gui->selection.active = false;
    gui->selection.index = -1;
    gui->selection.type = TYPE_NONE;
    gui->inspector.visible = false;
}
