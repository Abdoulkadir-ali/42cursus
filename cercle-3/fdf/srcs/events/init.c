/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:53:06 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 15:50:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	init_mouse(t_mouse *mouse)
{
	mouse->left_pressed = 0;
	mouse->right_pressed = 0;
	mouse->middle_pressed = 0;
	mouse->last_x = 0;
	mouse->last_y = 0;
	mouse->middle_start_x = 0;
	mouse->middle_start_y = 0;
}

void	init_keys(t_keys *keys)
{
	keys->up = 0;
	keys->down = 0;
	keys->left = 0;
	keys->right = 0;
	keys->ctrl_left = 0;
	keys->ctrl_right = 0;
	keys->shift_left = 0;
	keys->shift_right = 0;
	keys->l = 0;
	keys->z = 0;
	keys->f = 0;
	keys->h = 0;
	keys->d = 0;
	keys->t = 0;
	keys->s = 0;
	keys->a = 0;
	keys->x = 0;
	keys->i = 0;
	keys->v = 0;
	keys->g = 0;
}