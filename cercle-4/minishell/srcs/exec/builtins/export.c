/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 23:13:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_export_no_args(char ***envp)
{
	print_sorted_env(*envp);
	return (0);
}

static int	handle_invalid_option(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	if (arg[1] && arg[1] != '-')
	{
		write(2, "-", 1);
		write(2, &arg[1], 1);
	}
	else
		ft_putstr_fd(arg, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("export: usage: export [name[=value] ...] or export -p", 2);
	return (2);
}

static int	process_export_args(char **args, char ***envp)
{
	int	ret;
	int	arg_idx;

	ret = 0;
	arg_idx = 1;
	while (args[arg_idx])
	{
		if (args[arg_idx][0] == '-')
			return (handle_invalid_option(args[arg_idx]));
		if (process_export_arg(args[arg_idx], envp))
			ret = 1;
		arg_idx++;
	}
	return (ret);
}

int	ft_export(char **args, char ***envp)
{
	if (!args[1])
		return (handle_export_no_args(envp));
	return (process_export_args(args, envp));
}
