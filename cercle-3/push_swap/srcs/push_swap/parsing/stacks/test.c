/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:05:22 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 20:22:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_usage(char *program_name)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(program_name, 2);
	ft_putstr_fd(" <numbers>\n", 2);
}

static int	init_stacks_from_args(t_stacks *stacks, int argc, char **argv)
{
	char	**args;

	if (argc == 2)
	{
		args = ft_split(*argv, ' ');
		if (!args)
		{
			ft_putstr_fd("Error: ft_split failed\n", 2);
			return (0);
		}
		init_stacks(stacks, args);
		ft_free_split(args);
	}
	else
		init_stacks(stacks, argv);
	if (!stacks->a)
	{
		ft_putstr_fd("Error: parsing failed\n", 2);
		return (0);
	}
	return (1);
}

static void	print_parsed_numbers(t_stacks *stacks)
{
	t_nodes	*curr;
	char	*num_str;
	t_nodes	*start;

	ft_putstr_fd("Parsed numbers: ", 1);
	curr = stacks->a;
	if (curr)
	{
		start = curr;
		while (1)
		{
			num_str = ft_itoa(curr->v);
			ft_putstr_fd(num_str, 1);
			ft_putstr_fd(" ", 1);
			free(num_str);
			curr = curr->next;
			if (curr == start)
				break ;
		}
	}
	ft_putstr_fd("\n", 1);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	stacks = (t_stacks){NULL, NULL, 0};
	if (argc < 2)
	{
		print_usage(argv[0]);
		return (1);
	}
	argv++;
	if (!init_stacks_from_args(&stacks, argc, argv))
		return (1);
	print_parsed_numbers(&stacks);
	ft_clear(&stacks.a);
	ft_clear(&stacks.b);
	return (0);
}
