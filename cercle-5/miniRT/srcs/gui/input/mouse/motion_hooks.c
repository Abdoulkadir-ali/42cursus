/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 02:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 02:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	mlx_mouse_motion(int x, int y, void *param)
{
	t_gui	*gui;

	gui = (t_gui *)param;
	return (mouse_motion(vec2i(x, y), gui));
}

int	(*mouse_motion_hook(void))(int x, int y, void *param)
{
	return (mlx_mouse_motion);
}
