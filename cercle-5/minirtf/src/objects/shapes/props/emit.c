/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emit.c                                             :+:      :+:    :+:     */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 19:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "props_internal.h"

int	prop_emit_color(char **t, int n, t_scene *s)
{
	t_object	*arr;
	int		cnt;
	t_vec3		c;
	int			i;

	cnt = last_targets(s, &arr);
	if (cnt <= 0 || n != 2)
		return (0);
	if (!parse_color(t[1], &c))
		return (0);
	i = 0;
	while (i < cnt)
	{
		arr[i].mat.emit_color = c;
		if (arr[i].mat.emit_power <= 0.0f)
			arr[i].mat.emit_power = 1.0f;
		i++;
	}
	return (1);
}
