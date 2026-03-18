/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:15:13 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:15:14 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Handle `export` with no arguments by printing the sorted environment.
 * @param state Shell state providing the environment array.
 * @return Always returns 0.
 */
static int	handle_export_no_args(t_shell_state *state)
{
	print_sorted_env(state->envp);
	return (0);
}

/**
 * @brief Report an unsupported export option and print usage.
 * @param arg Invalid option token passed to export.
 * @return Shell usage error status 2.
 */
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

/**
 * @brief Process each export operand and update the environment.
 * @param args Argument vector passed to the export builtin.
 * @param state Active shell state receiving variable updates.
 * @return 0 on full success, 1 when at least one identifier is rejected.
 */
static int	process_export_args(char **args, t_shell_state *state)
{
	int	ret;
	int	arg_idx;

	ret = 0;
	arg_idx = 1;
	while (args[arg_idx])
	{
		if (args[arg_idx][0] == '-')
			return (handle_invalid_option(args[arg_idx]));
		if (process_export_arg(args[arg_idx], state))
			ret = 1;
		arg_idx++;
	}
	return (ret);
}

/**
 * @brief Execute the export builtin.
 * @param args Argument vector for export.
 * @param state Active shell state receiving environment changes.
 * @return Builtin status for the requested export operation.
 */
int	ft_export(char **args, t_shell_state *state)
{
	if (!args[1])
		return (handle_export_no_args(state));
	return (process_export_args(args, state));
}
