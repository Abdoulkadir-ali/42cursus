/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:17:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:14:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf_mode	fdf_detect_mode(const char *path)
{
	if (ft_strnstr(path, "generated_maps", ft_strlen(path)))
		return (FDF_MODE_PICTURE);
	if (ft_strnstr(path, "gradient", ft_strlen(path)))
		return (FDF_MODE_HEIGHT_GRADIENT);
	return (FDF_MODE_HEIGHT);
}

void	write_bgra(unsigned char *buf, int idx, t_vec3i rgb)
{
	buf[idx * 4 + 0] = (unsigned char)rgb.z;
	buf[idx * 4 + 1] = (unsigned char)rgb.y;
	buf[idx * 4 + 2] = (unsigned char)rgb.x;
	buf[idx * 4 + 3] = 0xFF;
}

char	*build_gradient_bitmap(void)
{
	unsigned char	*buf;
	int				i;
	int				t;

	buf = ft_calloc(1, 256 * 4);
	if (!buf)
		return (NULL);
	i = 0;
	while (i < 256)
	{
		t = i % 64;
		if (i < 64)
			write_bgra(buf, i, vec3i(0, t * 4, 255));
		else if (i < 128)
			write_bgra(buf, i, vec3i(0, 255, 255 - t * 4));
		else if (i < 192)
			write_bgra(buf, i, vec3i(t * 4, 255, 0));
		else
			write_bgra(buf, i, vec3i(255, 255 - t * 4, 0));
		i++;
	}
	return ((char *)buf);
}

char	*build_picture_bitmap(unsigned int *colors, size_t w, size_t h)
{
	unsigned char	*buf;
	size_t			i;
	unsigned int	c;

	buf = ft_calloc(1, w * h * 4);
	if (!buf)
		return (NULL);
	i = 0;
	while (i < w * h)
	{
		c = colors[i];
		write_bgra(buf, (int)i, vec3i((c >> 16) & 0xFF, (c >> 8) & 0xFF,
				c & 0xFF));
		i++;
	}
	return ((char *)buf);
}

void	fdf_apply_mode(t_mesh *mesh, t_scene *scene, t_fdf_state *state)
{
	free(mesh->uvs);
	mesh->uvs = NULL;
	if (state->mode == FDF_MODE_HEIGHT_GRADIENT)
		apply_height_gradient(mesh, scene);
	else if (state->mode == FDF_MODE_PICTURE)
		apply_picture(mesh, scene, state->dims, state->colors);
}
