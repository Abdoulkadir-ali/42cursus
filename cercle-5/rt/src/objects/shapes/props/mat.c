/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:49:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "props_internal.h"

int	prop_mat(char **t, int n, t_scene *s)
{
	t_object	*arr;
	t_vec3		a;
	t_vec3		b;
	int			ok;
	float		scale;
	int			tid;
	int			i;
	int			cnt;

	cnt = last_targets(s, &arr);
	if (cnt <= 0 || n < 3)
		return (0);
	if (!strcmp(t[1], "s") && n == 3)
	{
		if (!parse_color(t[2], &a))
			return (0);
		i = 0;
		while (i < cnt)
		{
			arr[i].mat.albedo = a;
			arr[i].mat.tex_id = -1;
			arr[i].color = a;
			i++;
		}
		return (1);
	}
	if (!strcmp(t[1], "c") && n == 5)
	{
		if (!parse_color(t[2], &a) || !parse_color(t[3], &b))
			return (0);
		scale = ft_atof_strict(t[4], &ok);
		if (!ok || scale <= 0.0f || scale > 1024.0f)
			return (0);
		tid = texture_make_checker(s, a, b, scale);
		if (tid < 0)
			return (0);
		i = 0;
		while (i < cnt)
		{
			arr[i].mat.tex_id = tid;
			arr[i].mat.albedo = (t_vec3){1, 1, 1};
			i++;
		}
		return (1);
	}
	if (n >= 5)
	{
		i = 0;
		while (i < cnt)
		{
			arr[i].mat.ks = ft_atof_strict(t[1], &ok);
			arr[i].mat.shininess = ft_atof_strict(t[2], &ok);
			arr[i].mat.reflectivity = ft_atof_strict(t[3], &ok);
			arr[i].mat.tex_id = ft_atoi_strict(t[4], &ok);
			if (n >= 6)
				arr[i].mat.temperature = ft_atof_strict(t[5], &ok);
			if (n >= 7)
				arr[i].mat.emission = ft_atof_strict(t[6], &ok);
			i++;
		}
		return (1);
	}
	return (0);
}
