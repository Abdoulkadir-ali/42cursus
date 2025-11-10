/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:33 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 16:13:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_buttons	init_buttons(void)
{
	t_buttons	buttons;

	// Keyboard keycodes (X11)
	buttons.keyboard.up_arrow = 65362;
	buttons.keyboard.down_arrow = 65364;
	buttons.keyboard.left_arrow = 65361;
	buttons.keyboard.right_arrow = 65363;
	buttons.keyboard.ctrl_left = 65507;
	buttons.keyboard.ctrl_right = 65508;
	buttons.keyboard.p = 112;
	buttons.keyboard.n = 110;
	buttons.keyboard.s = 115;
	buttons.keyboard.esc = 65307;
	buttons.keyboard.r = 114;

	// Mouse button codes
	buttons.mouse.left = 1;
	buttons.mouse.right = 3;
	buttons.mouse.middle = 2;
	buttons.mouse.scroll_up = 4;
	buttons.mouse.scroll_down = 5;

	return (buttons);
}
