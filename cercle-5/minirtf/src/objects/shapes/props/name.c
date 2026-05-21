/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:49:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "props_internal.h"

int	prop_name(char **t, int n, t_scene *s)
{
	t_object	*arr;
	int		cnt;
	int			i;

	cnt = last_targets(s, &arr);
	if (cnt <= 0 || n != 2)
		return (0);
	if (strlen(t[1]) >= MAT_NAME_LEN)
		return (0);
	i = 0;
	while (i < cnt)
	{
		strncpy(arr[i].mat.name, t[1], MAT_NAME_LEN - 1);
		arr[i].mat.name[MAT_NAME_LEN - 1] = '\0';
		i++;
	}
	return (1);
}
