/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 17:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	get_env_index(char *key, char **envp)
{
	int		i;
	int		len;

	len = ft_strlen(key);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_export(char **args, char ***envp)
{
	char	*key;
	int		idx;
	char	*new_entry;
	int		count;
	char	**new_env;
	char	*eq;
	int		i;

	if (!args[1])
		return (ft_env(*envp));
	eq = ft_strchr(args[1], '=');
	if (!eq)
		return (0);
	key = ft_substr(args[1], 0, eq - args[1]);
	idx = get_env_index(key, *envp);
	free(key);
	new_entry = ft_strdup(args[1]);
	if (idx != -1)
	{
		free((*envp)[idx]);
		(*envp)[idx] = new_entry;
	}
	else
	{
		count = 0;
		while ((*envp)[count]) count++;
		new_env = ft_calloc(count + 2, sizeof(char *));
		i = -1;
		while (++i < count) new_env[i] = (*envp)[i];
		new_env[count] = new_entry;
		free(*envp);
		*envp = new_env;
	}
	return (0);
}

int	ft_unset(char **args, char ***envp)
{
	int		idx;
	int		count;
	char	**new_env;
	int		i;
	int		j;

	if (!args[1])
		return (0);
	idx = get_env_index(args[1], *envp);
	if (idx == -1)
		return (0);
	count = 0;
	while ((*envp)[count]) count++;
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
	return (0);
}
