/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:38:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Reads a FBX binary node header (32 or 64 bit).
 */
void	fbx_read_header(int fd, t_fbx_bin_node *n, bool is_64)
{
	uint32_t	tmp[3];
	uint64_t	tmp64[3];

	ft_memset(n, 0, sizeof(*n));
	if (is_64)
	{
		if (read(fd, tmp64, 24) < 24)
			return ;
		n->end_offset = tmp64[0];
		n->num_properties = tmp64[1];
		n->property_list_len = tmp64[2];
	}
	else
	{
		if (read(fd, tmp, 12) < 12)
			return ;
		n->end_offset = tmp[0];
		n->num_properties = tmp[1];
		n->property_list_len = tmp[2];
	}
	if (read(fd, &n->name_len, 1) < 1)
		return ;
	if (n->name_len > 0)
		if (read(fd, n->name, n->name_len) < 1)
			return ;
	n->name[n->name_len] = '\0';
}

/**
 * @brief Skips a binary array property based on type and encoding.
 */
static void	skip_arr(int fd, char type)
{
	uint32_t	alen;
	uint32_t	enc;
	uint32_t	clen;
	size_t		isz;

	if (read(fd, &alen, 4) < 4 || read(fd, &enc, 4) < 4
		|| read(fd, &clen, 4) < 4)
		return ;
	if (enc == 1)
	{
		lseek(fd, clen, SEEK_CUR);
		return ;
	}
	isz = 1;
	if (type == 'd' || type == 'l')
		isz = 8;
	else if (type == 'f' || type == 'i')
		isz = 4;
	lseek(fd, (uint64_t)alen * isz, SEEK_CUR);
}

/**
 * @brief Skips FBX node properties.
 */
void	fbx_skip_props(int fd, uint64_t num)
{
	uint64_t	i;
	char		t;

	i = 0;
	while (i < num)
	{
		if (read(fd, &t, 1) < 1)
			break ;
		if (t == 'S' || t == 'R')
		{
			if (read(fd, &t, 4) < 4)
				break ;
			lseek(fd, (uint32_t)t, SEEK_CUR);
		}
		else if (ft_strchr("dflicb", t))
			skip_arr(fd, t);
		else if (t == 'I' || t == 'F')
			lseek(fd, 4, SEEK_CUR);
		else if (t == 'D' || t == 'L')
			lseek(fd, 8, SEEK_CUR);
		else if (t == 'Y')
			lseek(fd, 2, SEEK_CUR);
		i++;
	}
}
