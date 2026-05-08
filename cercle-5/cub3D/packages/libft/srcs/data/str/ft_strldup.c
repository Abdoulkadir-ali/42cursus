/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:51:21 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 19:51:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Performs string manipulation or inspection.
 * @note Public library exported function.
 */
char	*ft_strldup(char *str, size_t l)
{
	char	*r;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	while (*str && i < l)
		r[i++] = *str++;
	r[i] = 0;
	return (r);
}
