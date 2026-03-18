/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:16:09 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:16:10 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Build the final KEY=VALUE entry used by export append mode.
 * @param exp Export context containing the parsed key and suffix.
 * @return Newly allocated environment entry.
 */
char	*create_appended_entry(t_export *exp)
{
	char	*real_entry;
	char	*tmp;

	real_entry = ft_strjoin(exp->key, "=");
	tmp = real_entry;
	real_entry = ft_strjoin(real_entry, exp->eq + 1);
	free(tmp);
	return (real_entry);
}

/**
 * @brief Append a new entry to an environment array without shell-state sync.
 * @param envp Address of the environment array being extended.
 * @param new_entry Newly allocated environment entry.
 * @return This function does not return a value.
 */
void	push_new_env_entry(char ***envp, char *new_entry)
{
	size_t	count;
	char	**new_env;

	count = count_env(*envp);
	new_env = ft_calloc(count + 2, sizeof(char *));
	if (!new_env)
		return ;
	ft_memcpy(new_env, *envp, count * sizeof(char *));
	new_env[count] = new_entry;
	free(*envp);
	*envp = new_env;
}

/**
 * @brief Update an already existing environment variable during export.
 * @param exp Export context with the resolved index.
 * @param envp Address of the environment array being updated.
 * @return Always returns 0.
 */
int	process_existing_export(t_export *exp, char ***envp)
{
	update_existing_env(*envp, exp);
	free(exp->key);
	return (0);
}

/**
 * @brief Add a new variable to the environment during export.
 * @param exp Export context describing the new variable.
 * @param envp Address of the environment array being extended.
 * @return Always returns 0.
 */
int	process_new_export(t_export *exp, char ***envp)
{
	char	*real_entry;

	if (exp->append && exp->eq)
	{
		real_entry = create_appended_entry(exp);
		free(exp->new_entry);
		exp->new_entry = real_entry;
	}
	push_new_env_entry(envp, exp->new_entry);
	free(exp->key);
	return (0);
}
