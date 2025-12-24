/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:01:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/24 00:01:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

void	save_map_to_file(int **map, int w, int h, char *filename)
{
	int		fd;
	int		x;
	int		y;
	char	*str;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printf("Error: Could not open file %s for writing.\n", filename);
		return ;
	}
	ft_printf("Saving map to %s...\n", filename);
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			str = ft_itoa(map[y][x]);
			write(fd, str, ft_strlen(str));
			free(str);
			if (x < w - 1)
				write(fd, " ", 1);
			x++;
		}
		write(fd, "\n", 1);
		y++;
	}
	close(fd);
	ft_printf("Done!\n");
}
