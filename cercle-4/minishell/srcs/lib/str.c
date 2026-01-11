/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:31:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 00:55:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_any(char *s1, char *s2)
{
	if (ft_strchri(s2, *s1) != -1)
		return (1);
	return (0);
}

int	ft_strmatch(char *s1, char *s2, int (*match)(char *, char *))
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (match(&s1[i], s2))
			return (i);
		i++;
	}
	return (i);
}