/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:44:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:15:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Performs string manipulation or inspection.
 * @note Public library exported function.
 */
int	ft_strrchri(char *str, char c)
{
	size_t	i;

	if (!str)
		return (-1);
	i = ft_strlen(str);
	while (i)
	{
		if (str[i - 1] == c)
			return (i - 1);
		i++;
	}
	return (-1);
}
