/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:28:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include "stb_image_write.h"
#include <stdlib.h>

int	render_screenshot(t_app *app, const char *path)
{
	unsigned char	*rgb;
	int			x;
	int			y;
	unsigned int	px;
	const char	*row;

	if (!path || !app || !app->img.addr)
		return (-1);
	rgb = (unsigned char *)malloc((size_t)app->img.w * app->img.h * 3);
	if (!rgb)
		return (-1);
	y = 0;
	while (y < app->img.h)
	{
		row = app->img.addr + y * app->img.line_len;
		x = 0;
		while (x < app->img.w)
		{
			px = *(const unsigned int *)(row + x * 4);
			rgb[(y * app->img.w + x) * 3 + 0] = (px >> 16) & 0xff;
			rgb[(y * app->img.w + x) * 3 + 1] = (px >> 8) & 0xff;
			rgb[(y * app->img.w + x) * 3 + 2] = px & 0xff;
			x++;
		}
		y++;
	}
	if (!stbi_write_png(path, app->img.w, app->img.h, 3, rgb, app->img.w * 3))
	{
		free(rgb);
		return (-1);
	}
	free(rgb);
	return (0);
}
