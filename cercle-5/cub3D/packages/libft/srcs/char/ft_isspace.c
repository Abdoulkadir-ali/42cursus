/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 03:47:26 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 03:51:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Evaluates if input satisfies space condition.
 * @note Public library exported function.
 */
bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
