/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 03:08:59 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:13:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	parse_rgb_component(const char *str, size_t *i, int *out)
{
	*out = 0;
	*i = (size_t)(ft_skip_spaces(str + *i) - str);
	if (ft_isdigit(str[*i]) == 0)
		return (0);
	while (ft_isdigit(str[*i]) != 0)
		*out = *out * 10 + (str[(*i)++] - '0');
	if (*out < 0 || *out > 255)
		return (0);
	return (1);
}

int	parse_rgb_safe(const char *str, t_vec3 *out)
{
	size_t	i;
	int		value;

	i = 0;
	if (parse_rgb_component(str, &i, &value) == 0)
		return (0);
	out->x = (float)value;
	if (str[i++] != ',')
		return (0);
	if (parse_rgb_component(str, &i, &value) == 0)
		return (0);
	out->y = (float)value;
	if (str[i++] != ',')
		return (0);
	if (parse_rgb_component(str, &i, &value) == 0)
		return (0);
	out->z = (float)value;
	while (str[i] != '\0' && ft_isspace((unsigned char)str[i]) != 0)
		i++;
	return (str[i] == '\0');
}
