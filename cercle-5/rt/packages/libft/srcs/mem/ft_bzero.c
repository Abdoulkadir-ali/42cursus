/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:12 by abdali            #+#    #+#             */
/*   Updated: 2026/04/10 23:03:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Erases the data in the n bytes
 *  of the memory starting at the location pointed to by s by writing zeros.
 * 
 * @param s Target structural variable.
 * @param n Target structural variable.
 * @return void (Stateless void execution).
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
