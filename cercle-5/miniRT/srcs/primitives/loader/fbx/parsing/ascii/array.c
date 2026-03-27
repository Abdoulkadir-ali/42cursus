/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 22:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Logic for skiping non-numeric chars in FBX ASCII.
 */
static void	skip_non_num(char **p)
{
	while (**p != '\0' && !ft_isdigit(**p) && **p != '-' && **p != '.')
		(*p)++;
}

/**
 * @brief Parses a numeric array from FBX ASCII content.
 */
void	*fbx_parse_array_ascii(char **p, uint32_t *count, size_t elem_sz)
{
	void		*arr;
	uint32_t	cnt;
	uint32_t	i;

	skip_non_num(p);
	cnt = (uint32_t)ft_atoi(*p);
	*count = cnt;
	while (**p != '{')
		(*p)++;
	(*p)++;
	arr = malloc(cnt * elem_sz);
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < cnt)
	{
		if (elem_sz == 8)
			((double *)arr)[i] = ft_atof_advance(p);
		else
			((int *)arr)[i] = (int)ft_atoi_advance(p);
		i++;
	}
	return (arr);
}
