/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:21:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:21:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_stack_pop(t_stack *s)
{
	void	*item;

	if (!s || s->size == 0)
		return (NULL);
	item = s->items[s->size - 1];
	s->size--;
	return (item);
}
