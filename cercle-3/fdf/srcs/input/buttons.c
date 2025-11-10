/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:33 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:21:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_buttons	init_buttons(void)
{
	t_buttons	buttons;

	buttons.keyboard.up_arrow = 65362;
	buttons.keyboard.down_arrow = 65364;
	buttons.keyboard.left_arrow = 65361;
	buttons.keyboard.right_arrow = 65363;
	buttons.keyboard.ctrl_left = 65507;
	buttons.keyboard.ctrl_right = 65508;
	buttons.keyboard.shift_left = 65505;
	buttons.keyboard.shift_right = 65506;
	buttons.keyboard.p = 112;
	buttons.keyboard.n = 110;
	buttons.keyboard.s = 115;
	buttons.keyboard.esc = 65307;
	buttons.keyboard.r = 114;
	buttons.keyboard.l = 108;
	buttons.keyboard.z = 122;
	buttons.keyboard.f = 102;
	buttons.keyboard.h = 104;
	buttons.keyboard.d = 100;
	buttons.keyboard.t = 116;
	buttons.keyboard.a = 97;
	buttons.keyboard.x = 120;
	buttons.keyboard.i = 105;
	buttons.keyboard.v = 118;
	buttons.keyboard.plus = 61;
	buttons.keyboard.minus = 45;
	buttons.keyboard.zero = 48;
	buttons.mouse.left = 1;
	buttons.mouse.right = 3;
	buttons.mouse.middle = 2;
	buttons.mouse.scroll_up = 4;
	buttons.mouse.scroll_down = 5;
	return (buttons);
}
