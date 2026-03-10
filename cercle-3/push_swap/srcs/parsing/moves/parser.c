/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:14:24 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 22:44:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	execute_swap(t_stacks *s, char *line)
{
	if (ft_strcmp(line, "sa\n") == 0)
		sa(s);
	else if (ft_strcmp(line, "sb\n") == 0)
		sb(s);
	else if (ft_strcmp(line, "ss\n") == 0)
		ss(s);
	else
		return (0);
	return (1);
}

static int	execute_push(t_stacks *s, char *line)
{
	if (ft_strcmp(line, "pa\n") == 0)
		pa(s);
	else if (ft_strcmp(line, "pb\n") == 0)
		pb(s);
	else
		return (0);
	return (1);
}

static int	execute_reverse_rotate(t_stacks *s, char *line)
{
	if (ft_strcmp(line, "rra\n") == 0)
		rra(s);
	else if (ft_strcmp(line, "rrb\n") == 0)
		rrb(s);
	else if (ft_strcmp(line, "rrr\n") == 0)
		rrr(s);
	else
		return (0);
	return (1);
}

static int	execute_rotate(t_stacks *s, char *line)
{
	if (ft_strcmp(line, "ra\n") == 0)
		ra(s);
	else if (ft_strcmp(line, "rb\n") == 0)
		rb(s);
	else if (ft_strcmp(line, "rr\n") == 0)
		rr(s);
	else
		return (execute_reverse_rotate(s, line));
	return (1);
}

int	execute_instruction(t_stacks *s, char *line)
{
	if (execute_swap(s, line))
		return (1);
	if (execute_push(s, line))
		return (1);
	if (execute_rotate(s, line))
		return (1);
	return (0);
}
