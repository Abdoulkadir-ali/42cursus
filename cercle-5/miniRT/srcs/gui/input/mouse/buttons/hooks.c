/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:57:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	mlx_mouse_click(int b, int x, int y, void *p)
{
	return (mouse_click(b, vec2i(x, y), (t_gui *)p));
}

int	(*mouse_click_hook(void))(int b, int x, int y, void *p)
{
	return (mlx_mouse_click);
}

static int	mlx_mouse_release(int b, int x, int y, void *p)
{
	return (mouse_release(b, vec2i(x, y), (t_gui *)p));
}

int	(*mouse_release_hook(void))(int b, int x, int y, void *p)
{
	return (mlx_mouse_release);
}
