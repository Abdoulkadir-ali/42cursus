/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:12:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:13:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_buffer	*ft_buffer_new(size_t initial)
{
	t_buffer	*b;

	b = malloc(sizeof(*b));
	if (!b)
		return (NULL);
	b->cap = 64;
	if (initial)
		b->cap = 64;
	b->data = malloc(b->cap);
	if (!b->data)
	{
		free(b);
		return (NULL);
	}
	b->len = 0;
	b->data[0] = '\0';
	return (b);
}
