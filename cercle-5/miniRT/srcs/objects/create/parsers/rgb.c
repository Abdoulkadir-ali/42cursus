/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:07:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:14:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	is_rgb_int(char *s)
{
	int	val;

	if (!is_valid_int(s))
		return (false);
	val = ft_atoi(s);
	if (val < 0 || val > 255)
		return (false);
	return (true);
}

bool	is_valid_rgb(char *s)
{
	return (is_triple(s, &is_rgb_int));
}

bool	parse_rgb_to_matrix(t_matrix *m, char *s, void *(*conv)(const char *))
{
	parse_vector_to_matrix(m, s, conv);
}
