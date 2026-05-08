/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:33 by abdali            #+#    #+#             */
/*   Updated: 2026/03/25 14:29:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 *  Handles overlap securely.
 * 
 * @param d Target structural variable.
 * @param s Target structural variable.
 * @param n Target structural variable.
 * @return void * output natively.
 */
void	*ft_memmove(void *d, const void *s, size_t n)
{
	unsigned char	*dest;
	unsigned char	*src;

	dest = (unsigned char *)d;
	src = (unsigned char *)s;
	if (!n || dest == src)
		return (d);
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
		ft_memrcpy(dest, src, n);
	return ((void *)dest);
}
