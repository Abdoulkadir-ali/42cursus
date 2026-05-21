/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:47:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:47:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_strict(const char *s, int *ok)
{
	int		i;
	int		sign;
	long	v;

	i = 0;
	*ok = 0;
	sign = 1;
	if (!s)
		return (0);
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (s[i] < '0' || s[i] > '9')
		return (0);
	v = 0;
	while (s[i] >= '0' && s[i] <= '9')
		v = v * 10 + (s[i++] - '0');
	if (s[i] != '\0' || v > 2147483647L)
		return (0);
	*ok = 1;
	return ((int)(sign * v));
}
