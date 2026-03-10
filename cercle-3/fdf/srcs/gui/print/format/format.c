/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:38:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:51:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Format a speed multiplier as `NN.NNx`.
 * @param speed Numeric speed multiplier.
 * @param buffer Output buffer receiving the formatted string.
 */
void	format_speed(double speed, char *buffer)
{
	int	whole;
	int	decimal;

	whole = (int)speed;
	decimal = (int)((speed - whole) * 100);
	buffer[0] = '0' + (whole / 10);
	buffer[1] = '0' + (whole % 10);
	buffer[2] = '.';
	buffer[3] = '0' + (decimal / 10);
	buffer[4] = '0' + (decimal % 10);
	buffer[5] = 'x';
	buffer[6] = '\0';
}

/**
 * @brief Format a floating-point value with one decimal digit.
 * @param val Value to convert.
 * @param buffer Output buffer receiving the formatted string.
 */
void	format_float(double val, char *buffer)
{
	int	whole;
	int	decimal;
	int	i;

	whole = (int)val;
	decimal = (int)((val - whole) * 10);
	if (decimal < 0)
		decimal = -decimal;
	i = 0;
	if (whole >= 100)
	{
		buffer[i++] = '0' + (whole / 100);
		buffer[i++] = '0' + ((whole / 10) % 10);
	}
	else if (whole >= 10)
		buffer[i++] = '0' + (whole / 10);
	buffer[i++] = '0' + (whole % 10);
	buffer[i++] = '.';
	buffer[i++] = '0' + decimal;
	buffer[i] = '\0';
}
