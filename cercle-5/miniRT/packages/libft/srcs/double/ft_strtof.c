/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:40:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 06:48:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include <ctype.h>
#include <math.h>

float	ft_strtof(const char *s)
{
	double d = ft_strtod(s);
	return ((float)d);
}

