/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:21:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:21:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_stack_new(void)
{
	t_stack	*s;

	s = malloc(sizeof(t_stack));
	if (!s)
		return (NULL);
	s->items = malloc(sizeof(void *) * BUFFER_SIZE);
	if (!s->items)
	{
		free(s);
		return (NULL);
	}
	s->size = 0;
	s->cap = BUFFER_SIZE;
	return (s);
}
