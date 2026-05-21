/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:22:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stack_push(t_stack *s, void *item)
{
	if (!s)
		return (-1);
	if (ft_stack_reserve(s, 1) < 0)
		return (-1);
	s->items[s->size++] = item;
	return (0);
}
