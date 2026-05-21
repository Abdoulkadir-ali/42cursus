/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/10/17 00:19:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks for an alphanumeric character.
 * @note Public library exported function.
 */
bool	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
