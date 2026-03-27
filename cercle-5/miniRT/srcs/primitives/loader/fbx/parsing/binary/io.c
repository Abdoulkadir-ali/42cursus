/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

ssize_t	safe_read(int fd, void *buf, size_t count)
{
	return (read(fd, buf, count));
}

void	read_offsets(int fd, t_fbx_bin_node *node, bool is_64bit)
{
	uint32_t	tmp;

	if (is_64bit)
	{
		safe_read(fd, &node->end_offset, 8);
		safe_read(fd, &node->num_properties, 8);
		safe_read(fd, &node->property_list_len, 8);
	}
	else
	{
		safe_read(fd, &tmp, 4);
		node->end_offset = tmp;
		safe_read(fd, &tmp, 4);
		node->num_properties = tmp;
		safe_read(fd, &tmp, 4);
		node->property_list_len = tmp;
	}
}

void	read_node_header(int fd, t_fbx_bin_node *node, bool is_64bit)
{
	size_t	name_limit;
	size_t	to_read;

	read_offsets(fd, node, is_64bit);
	if (safe_read(fd, &node->name_len, 1) < 1)
	{
		node->end_offset = 0;
		return ;
	}
	ft_memset(node->name, 0, sizeof(node->name));
	if (node->name_len > 0)
	{
		name_limit = sizeof(node->name) - 1;
		to_read = node->name_len;
		if (to_read > name_limit)
			to_read = name_limit;
		safe_read(fd, node->name, to_read);
		if (node->name_len > to_read)
			lseek(fd, node->name_len - to_read, SEEK_CUR);
	}
}
