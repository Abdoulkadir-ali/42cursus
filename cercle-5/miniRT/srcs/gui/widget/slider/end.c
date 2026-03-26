/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:51:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	slider_end_drag(t_gui *gui)
{
    gui->slider_state->dragging = false;
    gui->slider_state->target = NULL;
}
