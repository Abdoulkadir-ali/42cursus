/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 04:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 03:49:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

int	json_arr_len(const char *p, const char *end)
{
	return (json_count_array(p, end));
}

long	json_int_idx(const char *p, const char *end, int i)
{
	return (json_int(json_arr_get(p, end, i), end));
}

double	json_flt_idx(const char *p, const char *end, int i)
{
	return (json_flt(json_arr_get(p, end, i), end));
}
