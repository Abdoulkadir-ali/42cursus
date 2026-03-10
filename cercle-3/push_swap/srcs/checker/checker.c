/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:14:19 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 00:02:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_output(t_stacks *stacks)
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

static int	handle_error(char *line, t_stacks stacks)
{
	ft_puterr("Error\n");
	free(line);
	free_stacks(stacks);
	return (1);
}

static int	process_instructions(t_stacks *stacks)
{
	char	*line;

	line = get_next_line(0);
	while (line && ft_strcmp(line, "\n"))
	{
		if (!execute_instruction(stacks, line))
			return (handle_error(line, *stacks));
		debug_line_stacks(*stacks, "After:", line);
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	return (0);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	if (argc < 2)
		return (0);
	init_stacks(&stacks, argv + 1);
	stacks.verbose = 0;
	debug_line_stacks(stacks, "Initial state:", NULL);
	if (process_instructions(&stacks))
		return (1);
	print_output(&stacks);
	free_stacks(stacks);
	return (0);
}
