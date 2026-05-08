/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:30 by abdali            #+#    #+#             */
/*   Updated: 2026/03/25 14:29:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 *  The memory areas must not overlap.
 * 
 * @param d Target structural variable.
 * @param s Target structural variable.
 * @param n Target structural variable.
 * @return void * output natively.
 */
void	*ft_memcpy(void *d, const void *s, size_t n)
{
	unsigned char	*dest;
	unsigned char	*src;
	size_t			i;

	dest = (unsigned char *)d;
	src = (unsigned char *)s;
	i = 0;
	while (i < n)
		dest[i++] = *src++;
	return ((void *)dest);
}
