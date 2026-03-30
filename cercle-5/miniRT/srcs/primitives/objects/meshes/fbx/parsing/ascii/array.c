/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

void	*parse_array(char **p, int *count, size_t sz, void (*f)(char **,
			void *))
{
	size_t	cap;
	size_t	i;
	void	*arr;

	cap = 10000;
	i = 0;
	arr = malloc(sz * cap);
	if (!arr)
		return (NULL);
	while (**p && **p != '}')
	{
		*p = fbx_next(*p);
		if (!**p || **p == '}')
			break ;
		if (!dynarray_ensure(&arr, i, &cap, sz))
			return (free(arr), NULL);
		f(p, (char *)arr + (i * sz));
		i++;
	}
	*count = (int)i;
	return (arr);
}

void	f_vec3(char **p, void *dst)
{
	t_vec3	*v;

	v = (t_vec3 *)dst;
	v->x = strtod(*p, p);
	*p = fbx_next(*p);
	v->y = strtod(*p, p);
	*p = fbx_next(*p);
	v->z = strtod(*p, p);
	if (**p == ',')
		(*p)++;
}

void	f_vec2(char **p, void *dst)
{
	t_vec2	*v;

	v = (t_vec2 *)dst;
	v->x = strtod(*p, p);
	*p = fbx_next(*p);
	v->y = strtod(*p, p);
	if (**p == ',')
		(*p)++;
}

void	f_int(char **p, void *dst)
{
	*(int *)dst = ft_atoi(*p);
	if (**p == '-')
		(*p)++;
	while (ft_isdigit(**p))
		(*p)++;
	if (**p == ',')
		(*p)++;
}
