/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:21:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:21:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stack_free(t_stack *s, void (*del)(void *))
{
	size_t	i;

	if (!s)
		return ;
	if (del)
	{
		i = 0;
		while (i < s->size)
		{
			if (s->items[i])
				del(s->items[i]);
			i++;
		}
	}
	free(s->items);
	free(s);
}
