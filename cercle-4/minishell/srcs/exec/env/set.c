/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:16:20 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/25 14:29:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Build one environment entry string from a key and optional value.
 * @param key Environment variable name.
 * @param value Optional value appended after `=`.
 * @return Newly allocated KEY=VALUE string, or NULL on allocation failure.
 */
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

/**
 * @brief Replace one existing environment entry in place.
 * @param envp Address of the environment array being updated.
 * @param idx Index of the entry that must be replaced.
 * @param new_entry Newly allocated replacement entry.
 * @param state Shell state that tracks the active environment pointer.
 * @return This function does not return a value.
 */
static void	replace_env_at(char ***envp, size_t idx, char *new_entry,
		t_shell_state *state)
{
	free((*envp)[idx]);
	(*envp)[idx] = new_entry;
	if (state->envp != *envp)
		state->envp = *envp;
}

/**
 * @brief Append one new environment entry to the environment array.
 * @param envp Address of the environment array being extended.
 * @param new_entry Newly allocated entry appended to the array.
 * @param state Shell state that tracks the active environment pointer.
 * @return 0 on success, 1 on allocation failure.
 */
static int	append_env_entry(char ***envp, char *new_entry,
		t_shell_state *state)
{
	size_t	count;
	char	**new_env;

	count = count_env(*envp);
	new_env = ft_calloc(count + 2, sizeof(char *));
	if (!new_env)
		return (1);
	ft_memcpy(new_env, *envp, count * sizeof(char *));
	new_env[count] = new_entry;
	free(*envp);
	*envp = new_env;
	if (state->envp != *envp)
		state->envp = *envp;
	return (0);
}

/**
 * @brief Find the index of one environment key in the active env array.
 * @param key Environment variable name to search for.
 * @param state Shell state providing the environment array.
 * @return Matching index, or -1 when the key is absent.
 */
int	get_env_index(char *key, t_shell_state *state)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (state->envp && state->envp[i])
	{
		if (ft_strncmp(state->envp[i], key, len) == 0
			&& (state->envp[i][len] == '=' || state->envp[i][len] == '\0'))
			return ((int)i);
		i++;
	}
	return (-1);
}

/**
 * @brief Insert or replace one environment variable in shell state.
 * @param key Environment variable name.
 * @param value Optional value stored after `=`.
 * @param state Shell state whose environment must be updated.
 * @return 0 on success, 1 when the update cannot be completed.
 */
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
		replace_env_at(&state->envp, (size_t)idx, new_entry, state);
	else
		append_env_entry(&state->envp, new_entry, state);
	return (0);
}
