/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   now.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:49:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:18:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"

long long		now_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
}