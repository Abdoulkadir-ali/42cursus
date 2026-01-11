/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:44:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 00:51:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrchri(char *str, char c)
{
	int i;

	if (!str)
		return (-1);
	i = (int)ft_strlen(str);
	while (i)
	{
		if (str[i - 1] == c)
			return (i - 1);
		i++;
	}
	return (-1);
}