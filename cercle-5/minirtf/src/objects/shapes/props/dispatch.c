/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:49:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "props_internal.h"

static int	prop_arity(const char *k)
{
	if (!strcmp(k, "rough") || !strcmp(k, "metal") || !strcmp(k, "refl")
		|| !strcmp(k, "opac") || !strcmp(k, "ior") || !strcmp(k, "emit_power")
		|| !strcmp(k, "temp") || !strcmp(k, "thermal") || !strcmp(k, "emit")
		|| !strcmp(k, "name"))
		return (2);
	return (0);
}

int	dispatch_one_prop(char **t, int n, t_scene *s)
{
	if (!strcmp(t[0], "rough"))
		return (prop_float(t, n, s, 0));
	if (!strcmp(t[0], "metal"))
		return (prop_float(t, n, s, 1));
	if (!strcmp(t[0], "refl"))
		return (prop_float(t, n, s, 2));
	if (!strcmp(t[0], "opac"))
		return (prop_float(t, n, s, 3));
	if (!strcmp(t[0], "ior"))
		return (prop_float(t, n, s, 4));
	if (!strcmp(t[0], "emit_power"))
		return (prop_float(t, n, s, 5));
	if (!strcmp(t[0], "temp"))
		return (prop_float(t, n, s, 6));
	if (!strcmp(t[0], "thermal"))
		return (prop_float(t, n, s, 7));
	if (!strcmp(t[0], "emit"))
		return (prop_emit_color(t, n, s));
	if (!strcmp(t[0], "name"))
		return (prop_name(t, n, s));
	return (0);
}

int	parse_property(char **t, int n, t_scene *s)
{
	int	i;
	int	a;

	if (n == 1 && !strcmp(t[0], "mat"))
		return (1);
	if (!strcmp(t[0], "mat"))
		return (prop_mat(t, n, s));
	i = 0;
	while (i < n)
	{
		a = prop_arity(t[i]);
		if (a == 0 || i + a > n)
			return (0);
		if (!dispatch_one_prop(t + i, a, s))
			return (0);
		i += a;
	}
	return (1);
}
