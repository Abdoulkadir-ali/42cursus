/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:13:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 20:34:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rotate(t_nodes **s)
{
	if (!s || !*s)
		return (0);
	if (ft_size(*s) < 2)
		return (1);
	*s = (*s)->next;
	return (1);
}

void	ra(t_stacks *s)
{
	if (rotate(&s->a) && s->verbose)
		ft_putstr_fd("ra\n", 1);
}

void	rb(t_stacks *s)
{
	if (rotate(&s->b) && s->verbose)
		ft_putstr_fd("rb\n", 1);
}

void	rr(t_stacks *s)
{
	rotate(&s->a);
	rotate(&s->b);
	if (s->verbose)
		ft_putstr_fd("rr\n", 1);
}
