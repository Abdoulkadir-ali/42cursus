/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:50:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:46:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "gui.h"

void	end_inline_drag(t_gui *gui)
{
	gui->slider_state.dragging = false;
	gui->slider_state.value_ptr = NULL;
	gui->slider_state.on_change = NULL;
	gui->slider_state.target = NULL;
}
