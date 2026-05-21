/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:17 by abdali            #+#    #+#             */
/*   Updated: 2025/11/04 09:54:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory for an array of nmemb elements
 *  of size bytes each and returns a pointer to the allocated memory.
 * 
 * @param nmemb Target structural variable.
 * @param size Target structural variable.
 * @return void * output natively.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	total;

	total = size * nmemb;
	if (size && total / size != nmemb)
		return (NULL);
	s = malloc(nmemb * size);
	if (!s)
		return (NULL);
	ft_bzero(s, nmemb * size);
	return (s);
}
