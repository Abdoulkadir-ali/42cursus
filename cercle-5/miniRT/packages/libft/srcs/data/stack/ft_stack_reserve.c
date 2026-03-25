/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_reserve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:22:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:29:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stack_reserve(t_stack *s, size_t additional)
{
	size_t	need;
	size_t	newcap;
	void	**tmp;

	if (!s)
		return (-1);
	need = s->size + additional;
	if (need <= (size_t)s->cap)
		return (0);
	newcap = s->cap;
	if (newcap == 0)
		newcap = BUFFER_SIZE;
	while (newcap < need)
		newcap <<= 1;
	tmp = malloc(newcap * sizeof(void *));
	if (!tmp)
		return (-1);
	if (s->items && s->size)
		ft_memcpy(tmp, s->items, s->size * sizeof(void *));
	free(s->items);
	s->items = tmp;
	s->cap = newcap;
	return (0);
}
