/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_stacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 23:40:47 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 23:53:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	debug_stacks(t_stacks s)
{
	print_stack(s.a, "stack a");
	print_stack(s.b, "stack b");
}

void	debug_line_stacks(t_stacks s, char *line, char *instruction)
{
	if (!DEBUG)
		return ;
	ft_putstr_fd(line, 2);
	if (instruction)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(instruction, 2);
	}
	ft_putstr_fd("\n", 2);
	debug_stacks(s);
	ft_putstr_fd("\n", 2);
}