/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:59:25 by abdoali           #+#    #+#             */
/*   Updated: 2025/10/19 12:59:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	if (argc != 2)
		return (0);
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	i = 0;
	while (i < atoi(argv[1]))
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("Line: %s\n", line);
			free(line);
		}
		i++;
	}
	close(fd);
	return (0);
}
