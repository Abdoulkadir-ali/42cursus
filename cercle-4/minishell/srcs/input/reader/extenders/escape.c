/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:39:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Check whether a trailing backslash is itself escaped.
 * @param line Full input line used as the left boundary for counting.
 * @param p Pointer to the backslash being inspected.
 * @return 1 when the backslash is an active escape, otherwise 0.
 */
int	handle_escape(char *line, char *p)
{
	int	count;

	count = 0;
	while (p >= line && *p == '\\')
	{
		count++;
		p--;
	}
	if (count % 2 != 0)
		return (1);
	return (0);
}
