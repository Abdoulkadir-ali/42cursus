/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:13:53 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 21:39:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_nodes	*pop_from_stack(t_nodes **s)
{
	t_nodes	*tmp;
	t_nodes	*last;

	if (!s || !*s)
		return (NULL);
	tmp = *s;
	if (ft_size(*s) == 1)
		*s = NULL;
	else
	{
		last = ft_last(*s);
		*s = tmp->next;
		last->next = *s;
	}
	tmp->next = NULL;
	return (tmp);
}

static void	push_to_stack(t_nodes **s, t_nodes *node)
{
	t_nodes	*last;

	if (!*s)
	{
		*s = node;
		node->next = node;
	}
	else
	{
		last = ft_last(*s);
		node->next = *s;
		last->next = node;
		*s = node;
	}
}

int	push(t_nodes **s1, t_nodes **s2)
{
	t_nodes	*tmp;

	tmp = pop_from_stack(s1);
	if (!tmp)
		return (0);
	push_to_stack(s2, tmp);
	return (1);
}

void	pa(t_stacks *s)
{
	if (push(&s->b, &s->a) && s->verbose)
		ft_putstr_fd("pa\n", 1);
}

void	pb(t_stacks *s)
{
	if (push(&s->a, &s->b) && s->verbose)
		ft_putstr_fd("pb\n", 1);
}
