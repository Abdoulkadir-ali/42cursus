/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/14 17:50:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_unset_handle_option(char *opt)
{
	ft_puterror("unset: %s: invalid option\n", opt);
	ft_puterror("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
	return (2);
}

static int	ft_unset_should_skip(char *arg)
{
	if (!is_valid_ident(arg) || ft_strchr(arg, '='))
		return (1);
	return (0);
}

static void	ft_unset_remove_at(char ***envp, int idx)
{
	int		count;
	char	**new_env;
	int		i;
	int		j;

	count = 0;
	while ((*envp)[count])
		count++;
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
}

int	ft_unset(char **args, char ***envp)
{
	int	idx;
	int	arg_idx;
	int	ret;

	if (!args[1])
		return (0);
	ret = 0;
	arg_idx = 1;
	while (args[arg_idx])
	{
		if (args[arg_idx][0] == '-')
			return (ft_unset_handle_option(args[arg_idx]));
		if (ft_unset_should_skip(args[arg_idx]))
		{
			arg_idx++;
			continue ;
		}
		idx = get_env_index(args[arg_idx], *envp);
		if (idx != -1)
			ft_unset_remove_at(envp, idx);
		arg_idx++;
	}
	return (ret);
}
