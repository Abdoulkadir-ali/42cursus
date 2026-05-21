/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_append_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:17:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:17:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_buffer_append_char(t_buffer *b, char c)
{
	if (!b)
		return (-1);
	if (ft_buffer_reserve(b, 1) < 0)
		return (-1);
	b->data[b->len++] = c;
	b->data[b->len] = '\0';
	return (0);
}
