/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:23:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Reset the keyboard state structure to the default released state.
 * @param keys Keyboard state structure to initialize.
 */
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
	keys->b = 0;
	keys->w = 0;
	keys->y = 0;
	keys->c = 0;
	keys->k = 0;
}
