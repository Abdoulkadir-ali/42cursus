/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 03:15:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/07 01:15:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

t_keymap_entry	*get_keyboard_keymap(void)
{
	static t_keymap_entry	keymap[] = {
	{XK_w, 0}, {XK_s, 1},
	{XK_a, 2}, {XK_d, 3},
	{XK_Left, 4}, {XK_Right, 5},
	{XK_Down, 6}, {XK_Up, 7},
	{XK_Return, 8}, {XK_r, 9},
	{XK_Shift_L, 10}, {XK_Control_L, 11},
	{XK_e, 12},
	{XK_space, 13},
	{XK_1, 14}, {XK_2, 15}, {XK_3, 16},
	{0, 0}};

	return (keymap);
}
