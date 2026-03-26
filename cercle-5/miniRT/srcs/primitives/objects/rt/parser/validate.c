/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	validate_file(const char *path)
{
	int	fd;

	if (!path || !*path)
		return (false);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nminiRT: ", 2);
		perror(path);
		return (false);
	}
	close(fd);
	return (true);
}
