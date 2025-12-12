/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:13:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 20:34:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	reverse_rotate(t_nodes **s)
{
	if (!s || !*s)
		return (0);
	if (ft_size(*s) < 2)
		return (1);
	*s = ft_last(*s);
	return (1);
}

void	rra(t_stacks *s)
{
	if (reverse_rotate(&s->a) && s->verbose)
		ft_putstr_fd("rra\n", 1);
}

void	rrb(t_stacks *s)
{
	if (reverse_rotate(&s->b) && s->verbose)
		ft_putstr_fd("rrb\n", 1);
}

void	rrr(t_stacks *s)
{
	if (reverse_rotate(&s->a) && reverse_rotate(&s->b) && s->verbose)
		ft_putstr_fd("rrr\n", 1);
}
