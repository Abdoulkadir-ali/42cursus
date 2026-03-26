/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 04:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"

/**
 * @brief Converts RGBA data into BGRA format for MLX compatibility.
 * @param data The raw pixel data.
 * @param size The total size of the data in bytes.
 */
void	convert_rgba_to_bgra(unsigned char *data, int size)
{
	unsigned char	tmp;
	int				i;

	i = 0;
	while (i < size)
	{
		tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
		i += 4;
	}
}
