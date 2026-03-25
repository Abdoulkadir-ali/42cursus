/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:41 by abdali            #+#    #+#             */
/*   Updated: 2025/11/04 09:57:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Performs raw physical memory block
 *  operations dynamically, copying in reverse.
 * @param d Target structural variable.
 * @param s Target structural variable.
 * @param n Target structural variable.
 * @return void * output natively.
 */
void	*ft_memrcpy(void *d, const void *s, size_t n)
{
	unsigned char	*dest;
	unsigned char	*src;

	dest = (unsigned char *)d;
	src = (unsigned char *)s;
	while (n)
	{
		dest[n - 1] = src[n - 1];
		n--;
	}
	return ((void *)dest);
}
