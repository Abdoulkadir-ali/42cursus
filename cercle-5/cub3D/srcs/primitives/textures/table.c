/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 01:40:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

static void	fill_lookup(t_xpm *xpm, size_t i, unsigned int hash)
{
	while (xpm->table[hash].idx != 0)
		hash = (hash + 1) & (xpm->table_size - 1);
	xpm->table[hash].key = xpm->colors[i].key;
	xpm->table[hash].idx = (unsigned int)i + 1;
}

int	xpm_init_table(t_xpm *xpm)
{
	size_t			i;
	unsigned int	hash;

	xpm->table_size = 1;
	while (xpm->table_size < xpm->ncolors * 2)
		xpm->table_size <<= 1;
	xpm->table = ft_calloc(xpm->table_size, sizeof(t_xpm_lookup));
	if (!xpm->table)
		return (1);
	i = 0;
	while (i < xpm->ncolors)
	{
		hash = (xpm->colors[i].key * XPM_HASH_MULT) & (xpm->table_size - 1);
		fill_lookup(xpm, i, hash);
		i++;
	}
	return (0);
}

int	xpm_read_header(t_xpm *xpm)
{
	char	*line;

	while (parser_read_line_alloc(xpm->parser, &line))
	{
		if (line[0] == '"')
		{
			parse_xpm_header(xpm, line);
			free(line);
			return (0);
		}
		free(line);
	}
	return (1);
}
