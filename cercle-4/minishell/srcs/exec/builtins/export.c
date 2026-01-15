/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:48:24 by abdoali          ###   ########.fr       */
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
	char	opt[3];

	if (arg[1] && arg[1] != '-')
	{
		opt[0] = '-';
		opt[1] = arg[1];
		opt[2] = '\0';
		ft_puterror("export: %s: invalid option\n", opt);
	}
	else
		ft_puterror("export: %s: invalid option\n", arg);
	ft_puterror("export: usage: export [name[=value] ...] or export -p\n");
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
