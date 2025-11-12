/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:38:24 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 15:48:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	format_depth_str(int percent, char *str)
{
	str[0] = '0' + (percent / 10);
	str[1] = '0' + (percent % 10);
	str[2] = '%';
	str[3] = ' ';
	str[4] = 'v';
	str[5] = 'i';
	str[6] = 's';
	str[7] = 'i';
	str[8] = 'b';
	str[9] = 'l';
	str[10] = 'e';
	str[11] = '\0';
}

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

void	format_number(int num, char *buffer)
{
	int	i;
	int	temp;

	if (num == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return ;
	}
	i = 0;
	temp = num;
	while (temp > 0)
	{
		buffer[i++] = '0' + (temp % 10);
		temp /= 10;
	}
	buffer[i] = '\0';
	temp = 0;
	while (temp < i / 2)
	{
		buffer[temp] ^= buffer[i - 1 - temp];
		buffer[i - 1 - temp] ^= buffer[temp];
		buffer[temp] ^= buffer[i - 1 - temp];
		temp++;
	}
}

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
	if (whole >= 10)
		buffer[i++] = '0' + (whole / 10);
	buffer[i++] = '0' + (whole % 10);
	buffer[i++] = '.';
	buffer[i++] = '0' + decimal;
	buffer[i] = '\0';
}
