/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:12:39 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 22:16:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	swap(t_nodes **s)
{
	t_nodes	*s1;
	t_nodes	*s2;
	t_nodes	*last;

	if (!s || !*s)
		return (0);
	if (ft_size(*s) == 1)
		return (1);
	s1 = *s;
	s2 = (*s)->next;
	if (ft_size(*s) == 2)
	{
		*s = s2;
		return (1);
	}
	last = ft_last(*s);
	s1->next = s2->next;
	s2->next = s1;
	last->next = s2;
	*s = s2;
	return (1);
}

void	sa(t_stacks *s)
{
	if (swap(&s->a) && s->verbose)
		ft_putstr_fd("sa\n", 1);
}

void	sb(t_stacks *s)
{
	if (swap(&s->b) && s->verbose)
		ft_putstr_fd("sb\n", 1);
}

void	ss(t_stacks *s)
{
	swap(&s->a);
	swap(&s->b);
	if (s->verbose)
		ft_putstr_fd("ss\n", 1);
}
