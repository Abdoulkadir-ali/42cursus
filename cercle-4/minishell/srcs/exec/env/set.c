/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 13:58:34 by abdoali          ###   ########.fr       */
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

static void	replace_env_at(char ***envp, int idx, char *new_entry,
		t_shell_state *state)
{
	free((*envp)[idx]);
	(*envp)[idx] = new_entry;
	if (state->envp != *envp)
		state->envp = *envp;
}

static int	append_env_entry(char ***envp, char *new_entry,
		t_shell_state *state)
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
	if (state->envp != *envp)
		state->envp = *envp;
	return (0);
}

int	get_env_index(char *key, t_shell_state *state)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (state->envp && state->envp[i])
	{
		if (ft_strncmp(state->envp[i], key, len) == 0
			&& (state->envp[i][len] == '=' || state->envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_set_env(char *key, char *value, t_shell_state *state)
{
	char	*new_entry;
	int		idx;

	if (!key || !state->envp)
		return (1);
	new_entry = make_new_entry(key, value);
	if (!new_entry)
		return (1);
	idx = get_env_index(key, state);
	if (idx != -1)
		replace_env_at(&state->envp, idx, new_entry, state);
	else
		append_env_entry(&state->envp, new_entry, state);
	return (0);
}
