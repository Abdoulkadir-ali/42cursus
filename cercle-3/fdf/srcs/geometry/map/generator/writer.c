/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

/**
 * @brief Write one row of height values to a file.
 * @param fd Destination file descriptor.
 * @param row Height row to serialize.
 * @param w Number of values in the row.
 */
static void	write_row(int fd, int *row, int w)
{
	t_vec2	pos;
	char	*str;

	pos.x = 0;
	while (pos.x < w)
	{
		str = ft_itoa(row[pos.x]);
		write(fd, str, ft_strlen(str));
		free(str);
		if (pos.x < w - 1)
			write(fd, " ", 1);
		pos.x++;
	}
	write(fd, "\n", 1);
}

/**
 * @brief Save a generated heightmap to a `.fdf`-compatible file.
 * @param map Heightmap to serialize.
 * @param w Map width.
 * @param h Map height.
 * @param filename Output filename.
 */
void	save_map_to_file(int **map, int w, int h, char *filename)
{
	int		fd;
	t_vec2	pos;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printf("Error: Could not open file %s for writing.\n", filename);
		return ;
	}
	ft_printf("Saving map to %s...\n", filename);
	pos.y = 0;
	while (pos.y < h)
	{
		write_row(fd, map[pos.y], w);
		pos.y++;
	}
	close(fd);
	ft_printf("Done!\n");
}
