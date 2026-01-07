/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 21:09:21 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/29 21:09:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnstr(const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] && i < n)
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}
