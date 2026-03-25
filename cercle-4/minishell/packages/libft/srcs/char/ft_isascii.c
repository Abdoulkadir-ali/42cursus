/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:04:22 by abdali            #+#    #+#             */
/*   Updated: 2026/03/25 14:11:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks whether c is a 7-bit unsigned 
 * char value that fits into the ASCII character set.
 * @note Public library exported function.
 */
bool	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
