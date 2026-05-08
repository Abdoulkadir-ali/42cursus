/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:33:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:33:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

int	handle_mouse_release(int button, int x, int y, void *param)
{
	t_player_controller	*ctrl;

	ctrl = (t_player_controller *)param;
	(void)x;
	(void)y;
	if (button == 1)
		ctrl->mouse.lmb_pressed = 0;
	return (0);
}
