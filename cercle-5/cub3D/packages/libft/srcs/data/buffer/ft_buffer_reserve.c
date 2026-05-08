/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_reserve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:14:53 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:29:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_buffer_reserve(t_buffer *b, size_t additional)
{
	size_t	need;
	size_t	newcap;
	char	*tmp;

	if (!b)
		return (-1);
	need = b->len + additional + 1;
	if (need <= b->cap)
		return (0);
	newcap = b->cap;
	if (newcap == 0)
		newcap = BUFFER_SIZE;
	while (newcap < need)
		newcap <<= 1;
	tmp = malloc(newcap);
	if (!tmp)
		return (-1);
	if (b->data && b->len)
		ft_memcpy(tmp, b->data, b->len);
	tmp[b->len] = '\0';
	free(b->data);
	b->data = tmp;
	b->cap = newcap;
	return (0);
}
