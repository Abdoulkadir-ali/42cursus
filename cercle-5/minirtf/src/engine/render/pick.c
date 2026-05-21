/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 18:47:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

int	pick_alloc(t_pickbuf *pb, int w, int h)
{
	free(pb->ids);
	pb->ids = (int *)malloc(sizeof(int) * (size_t)w * (size_t)h);
	if (!pb->ids)
		return (-1);
	pb->w = w;
	pb->h = h;
	return (0);
}

void	pick_free(t_pickbuf *pb)
{
	free(pb->ids);
	pb->ids = NULL;
	pb->w = 0;
	pb->h = 0;
}

int	pick_at(t_app *app, int sx, int sy)
{
	if (!app->pick.ids || sx < 0 || sy < 0
		|| sx >= app->pick.w || sy >= app->pick.h)
		return (0x7fffffff);
	return (app->pick.ids[sy * app->pick.w + sx]);
}