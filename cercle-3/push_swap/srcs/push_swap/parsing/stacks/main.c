/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:35:06 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 21:47:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	init_checker(t_stacks *stacks, int argc, char **argv)
{
	*stacks = (t_stacks){NULL, NULL, 0};
	if (argc < 2)
		return (0);
	argv++;
	init_stacks(stacks, argv);
	stacks->verbose = 0;
	if (!stacks->a)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	return (1);
}

static void	process_instructions(t_stacks *stacks)
{
	char	*line;
	size_t	len;

	line = get_next_line(0);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		execute_instruction(stacks, line);
		free(line);
		line = get_next_line(0);
	}
}

static void	print_result(t_stacks *stacks)
{
	if (is_sorted(stacks->a) && !stacks->b)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	if (!init_checker(&stacks, argc, argv))
		return (0);
	process_instructions(&stacks);
	print_result(&stacks);
	free_stacks(stacks);
	return (0);
}
