/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:22 by abdali            #+#    #+#             */
/*   Updated: 2025/11/04 09:56:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Scans the initial n bytes of the memory area
 *  pointed to by s for the first instance of c.
 * 
 * @param s Target structural variable.
 * @param c Target structural variable.
 * @param n Target structural variable.
 * @return void * output natively.
 */
void	*ft_memchr(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	byte;

	i = 0;
	str = (unsigned char *)s;
	byte = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == byte)
			return ((void *)&str[i]);
		i++;
	}
	return ((void *)0);
}
