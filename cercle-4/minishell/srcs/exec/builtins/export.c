/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 03:20:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	ft_export(char **args, char ***envp)
{
	int	ret;
	int	arg_idx;

	if (!args[1])
	{
		print_sorted_env(*envp);
		return (0);
	}
	ret = 0;
	arg_idx = 1;
	while (args[arg_idx])
	{
		if (args[arg_idx][0] == '-')
		{
			ft_putstr_fd("minishell: export: ", 2);
			if (args[arg_idx][1] && args[arg_idx][1] != '-')
			{
				write(2, "-", 1);
				write(2, &args[arg_idx][1], 1);
			}
			else
				ft_putstr_fd(args[arg_idx], 2);
			ft_putendl_fd(": invalid option", 2);
			ft_putendl_fd("export: usage: export [name[=value] ...] or export -p", 2);
			return (2);
		}
		if (process_export_arg(args[arg_idx], envp))
			ret = 1;
		arg_idx++;
	}
	return (ret);
}
