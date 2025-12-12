/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:14:19 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 23:53:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_output(t_stacks *stacks)
{
	if (is_sorted(stacks->a) && stacks->b == NULL)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	if (DEBUG)
	{
		stacks->verbose = 1;
		debug_stacks(*stacks);
	}
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	char		*line;

	if (argc < 2)
		return (0);
	init_stacks(&stacks, argv + 1);
	stacks.verbose = 0;
	debug_line_stacks(stacks, "Initial state:", NULL);
	line = get_next_line(0);
	while (line && ft_strcmp(line, "\n"))
	{
		if (!execute_instruction(&stacks, line))
		{
			ft_puterr("Error\n");
			free(line);
			free_stacks(stacks);
			return (1);
		}
		debug_line_stacks(stacks, "After:", line);
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	print_output(&stacks);
	free_stacks(stacks);
	return (0);
}
