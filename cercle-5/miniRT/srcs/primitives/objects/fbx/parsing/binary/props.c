/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static size_t	fbx_array_elem_size(char type)
{
	if (type == 'd' || type == 'l')
		return (8);
	if (type == 'f' || type == 'i')
		return (4);
	return (1);
}

static void	skip_string_prop(int fd)
{
	uint32_t	slen;

	if (safe_read(fd, &slen, 4) < 4)
		return ;
	lseek(fd, slen, SEEK_CUR);
}

static void	skip_array_prop(int fd, char type)
{
	uint32_t	alen;
	uint32_t	enc;
	uint32_t	clen;
	size_t		isz;

	if (safe_read(fd, &alen, 4) < 4 || safe_read(fd, &enc, 4) < 4
		|| safe_read(fd, &clen, 4) < 4)
		return ;
	if (enc == 1)
	{
		lseek(fd, clen, SEEK_CUR);
		return ;
	}
	isz = fbx_array_elem_size(type);
	lseek(fd, (uint64_t)alen * isz, SEEK_CUR);
}

void	skip_properties(int fd, uint64_t num_props)
{
	uint64_t	i;
	char		type;

	i = 0;
	while (i < num_props)
	{
		if (safe_read(fd, &type, 1) < 1)
			break ;
		if (type == 'Y')
			lseek(fd, 2, SEEK_CUR);
		else if (type == 'C')
			lseek(fd, 1, SEEK_CUR);
		else if (type == 'I' || type == 'F')
			lseek(fd, 4, SEEK_CUR);
		else if (type == 'D' || type == 'L')
			lseek(fd, 8, SEEK_CUR);
		else if (type == 'S' || type == 'R')
			skip_string_prop(fd);
		else if (ft_strchr("dflicb", type))
			skip_array_prop(fd, type);
		i++;
	}
}
