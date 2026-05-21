/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:49:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "props_internal.h"

int	prop_float(char **t, int n, t_scene *s, int field)
{
	t_object	*arr;
	int		cnt;
	int		ok;
	float		v;
	int		i;

	cnt = last_targets(s, &arr);
	if (cnt <= 0 || n != 2)
		return (0);
	v = ft_atof_strict(t[1], &ok);
	if (!ok)
		return (0);
	i = 0;
	while (i < cnt)
	{
		if (field == 0)
		{
			if (v < 0.0f || v > 1.0f)
				return (0);
			arr[i].mat.roughness = v;
			arr[i].mat.shininess = 2.0f / fmaxf(0.0001f, v * v) - 2.0f;
			if (arr[i].mat.shininess > 1024.0f)
				arr[i].mat.shininess = 1024.0f;
			if (arr[i].mat.shininess < 1.0f)
				arr[i].mat.shininess = 1.0f;
			arr[i].mat.ks = 0.04f + 0.6f * (1.0f - v);
		}
		else if (field == 1)
		{
			if (v < 0.0f || v > 1.0f)
				return (0);
			arr[i].mat.metallic = v;
		}
		else if (field == 2)
		{
			if (v < 0.0f || v > 1.0f)
				return (0);
			arr[i].mat.reflectivity = v;
		}
		else if (field == 3)
		{
			if (v < 0.0f || v > 1.0f)
				return (0);
			arr[i].mat.opacity = v;
		}
		else if (field == 4)
		{
			if (v < 1.0f || v > 3.0f)
				return (0);
			arr[i].mat.ior = v;
		}
		else if (field == 5)
		{
			if (v < 0.0f || v > 64.0f)
				return (0);
			arr[i].mat.emit_power = v;
		}
		else if (field == 6)
		{
			if (v < 0.0f || v > 40000.0f)
				return (0);
			arr[i].mat.temperature = v;
		}
		else if (field == 7)
		{
			if (v < 0.0f || v > 64.0f)
				return (0);
			arr[i].mat.emission = v;
		}
		i++;
	}
	return (1);
}
