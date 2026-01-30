/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:03:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 04:39:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	is_valid_int(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (false);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

int	*parse_int(char *s)
{
	int	*res;

	if (!s || !is_valid_int(s))
		return (NULL);
	res = malloc(sizeof(*res));
	if (!res)
		return (NULL);
	*res = ft_atoi(s);
	return (res);
}
