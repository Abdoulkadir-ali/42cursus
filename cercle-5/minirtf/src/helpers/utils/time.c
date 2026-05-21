/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:52:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

double	time_ms_now(void)
{
	struct timespec	t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec * 1000.0 + t.tv_nsec / 1.0e6);
}