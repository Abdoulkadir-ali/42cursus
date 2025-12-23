/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:06:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	reverse_digits(char *buffer, int start, int end)
{
	char	tmp_char;

	while (start < end)
	{
		tmp_char = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = tmp_char;
		start++;
		end--;
	}
}

void	format_number(long long num, char *buffer)
{
	long long	val;
	int			i;
	int			start_reversal;

	if (num == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return ;
	}
	i = 0;
	val = num;
	if (val < 0)
	{
		buffer[i++] = '-';
		val = -val;
	}
	start_reversal = i;
	while (val > 0)
	{
		buffer[i++] = '0' + (val % 10);
		val /= 10;
	}
	buffer[i] = '\0';
	reverse_digits(buffer, start_reversal, i - 1);
}
