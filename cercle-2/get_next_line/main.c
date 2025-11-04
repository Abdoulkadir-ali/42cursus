/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:13:53 by abdoali           #+#    #+#             */
/*   Updated: 2025/10/23 19:13:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	main(int argc, char **argv)
{
	int	l;
	int	fd;
	int	i;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (0);
	if (argc >= 2)
	{
		l = atoi(argv[1]);
		i = 0;
		while (i < l)
		{
			ft_putstr(get_next_line(fd));
			i++;
		}
	}
	else
		ft_putstr(get_next_line(fd));
	close(fd);
	return (0);
}
