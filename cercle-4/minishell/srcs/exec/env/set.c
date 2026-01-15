/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 13:51:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*make_new_entry(char *key, char *value)
{
	char	*entry;
	char	*tmp;

	entry = ft_strjoin(key, "=");
	if (!entry)
		return (NULL);
	if (value)
	{
		tmp = entry;
		entry = ft_strjoin(entry, value);
		free(tmp);
	}
	return (entry);
}

static void	replace_env_at(char ***envp, int idx, char *new_entry)
{
	free((*envp)[idx]);
	(*envp)[idx] = new_entry;
}

static int	append_env_entry(char ***envp, char *new_entry)
{
	int		count;
	char	**new_env;
	int		i;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = ft_calloc(count + 2, sizeof(char *));
	if (!new_env)
		return (1);
	i = -1;
	while (++i < count)
		new_env[i] = (*envp)[i];
	new_env[count] = new_entry;
	free(*envp);
	*envp = new_env;
	return (0);
}

int	get_env_index(char *key, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && (envp[i][len] == '='
			|| envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_set_env(char *key, char *value, char ***envp)
{
	char	*new_entry;
	int		idx;

	if (!key || !envp || !*envp)
		return (1);
	new_entry = make_new_entry(key, value);
	if (!new_entry)
		return (1);
	idx = get_env_index(key, *envp);
	if (idx != -1)
		replace_env_at(envp, idx, new_entry);
	else
		append_env_entry(envp, new_entry);
	return (0);
}
