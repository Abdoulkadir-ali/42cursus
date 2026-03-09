/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Report an unsupported option passed to unset.
 * @param opt Invalid option token.
 * @return Shell usage error status 2.
 */
static int	ft_unset_handle_option(char *opt)
{
	ft_puterror("unset: %s: invalid option\n", opt);
	ft_puterror("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
	return (2);
}

/**
 * @brief Remove one environment entry from the shell environment array.
 * @param envp Address of the environment array to rebuild.
 * @param idx Index of the entry that must be removed.
 * @param state Shell state keeping a pointer to the active environment.
 * @return This function does not return a value.
 */
static void	ft_unset_remove_at(char ***envp, int idx, t_shell_state *state)
{
	int		count;
	char	**new_env;
	int		i;
	int		j;

	count = count_env(*envp);
	new_env = ft_calloc(count, sizeof(char *));
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i != idx)
			new_env[j++] = (*envp)[i];
		else
			free((*envp)[i]);
		i++;
	}
	free(*envp);
	*envp = new_env;
	if (state->envp != *envp)
		state->envp = *envp;
}

/**
 * @brief Execute the unset builtin for each valid identifier argument.
 * @param args Argument vector containing names to remove.
 * @param state Active shell state whose environment is updated.
 * @return Builtin status for the unset operation.
 */
int	ft_unset(char **args, t_shell_state *state)
{
	int	idx;
	int	arg_idx;
	int	ret;

	ret = 0;
	arg_idx = 1;
	while (args[arg_idx])
	{
		if (args[arg_idx][0] == '-')
			return (ft_unset_handle_option(args[arg_idx]));
		if (!is_valid_ident(args[arg_idx]) || ft_strchr(args[arg_idx], '='))
		{
			arg_idx++;
			continue ;
		}
		idx = get_env_index(args[arg_idx], state);
		if (idx != -1)
			ft_unset_remove_at(&state->envp, idx, state);
		arg_idx++;
	}
	return (ret);
}
