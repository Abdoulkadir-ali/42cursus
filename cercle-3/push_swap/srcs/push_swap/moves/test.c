/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:08:51 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 21:34:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_usage(char *program_name)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(program_name, 2);
	ft_putstr_fd(" \"<numbers>\" <moves>...\n", 2);
}

static void	process_moves(t_stacks *stacks, int argc, char **argv)
{
	int		i;
	char	*move_nl;

	i = 2;
	while (i < argc)
	{
		move_nl = ft_strjoin(argv[i], "\n");
		if (!execute_instruction(stacks, move_nl))
		{
			ft_putstr_fd("Unknown move: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("\n", 2);
		}
		free(move_nl);
		i++;
	}
}

static int	check_result(t_stacks *stacks)
{
	if (is_sorted(stacks->a) && !stacks->b)
	{
		ft_putstr_fd("OK: Stack is sorted and B is empty\n", 1);
		return (1);
	}
	else
	{
		ft_putstr_fd("ERROR: Stack is not sorted or B is not empty\n", 2);
		debug_stacks(*stacks);
		return (0);
	}
}

static int	init_and_validate_stacks(t_stacks *stacks, char **argv)
{
	char	**args;

	args = ft_split(argv[1], ' ');
	if (!args)
	{
		ft_putstr_fd("Error: ft_split failed\n", 2);
		return (0);
	}
	init_stacks(stacks, args);
	stacks->verbose = 0;
	ft_free_split(args);
	if (!stacks->a)
	{
		ft_putstr_fd("Error: parsing initial stack failed\n", 2);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	stacks = (t_stacks){NULL, NULL, 0};
	if (argc < 3)
	{
		print_usage(argv[0]);
		return (1);
	}
	if (!init_and_validate_stacks(&stacks, argv))
		return (1);
	process_moves(&stacks, argc, argv);
	if (!check_result(&stacks))
	{
		free_stacks(stacks);
		return (1);
	}
	free_stacks(stacks);
	return (0);
}
