/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:17:19 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:29:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_data(t_buffer *b, const char *s, size_t n)
{
	if (n)
		ft_memcpy(b->data + b->len, s, n);
}

int	ft_buffer_append(t_buffer *b, const char *s, size_t n)
{
	if (!b || (!s && n))
		return (-1);
	if (ft_buffer_reserve(b, n) < 0)
		return (-1);
	copy_data(b, s, n);
	b->len += n;
	b->data[b->len] = '\0';
	return (0);
}
