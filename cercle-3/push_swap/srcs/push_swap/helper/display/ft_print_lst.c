/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 21:33:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_stack_values(t_nodes *stack)
{
	int	size;

	if (!stack)
		return ;
	size = ft_size(stack);
	while (size)
	{
		ft_putnbr_fd(stack->v, 1);
		ft_putstr_fd(", ", 1);
		stack = stack->next;
		size--;
	}
	ft_putstr_fd("\b\b", 1);
}

void	print_stack(t_nodes *stack, char *name)
{
	ft_putstr_fd(name, 1);
	ft_putstr_fd(" : ", 1);
	if (!stack)
		ft_putstr_fd("(empty)", 1);
	else
		print_stack_values(stack);
	ft_putstr_fd("\n", 1);
}

void	debug_stacks(t_stacks s)
{
	print_stack(s.a, "stack a");
	print_stack(s.b, "stack b");
}
