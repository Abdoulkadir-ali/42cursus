/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:22:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @param envp Environment array containing the entry to update.
 * @param exp Export context with the target index and suffix.
 * @return This function does not return a value.
 */
static void	handle_append(char **envp, t_export *exp)
{
	char	*joined;
	char	*tmp;

	if (ft_strchr(envp[exp->idx], '='))
		joined = ft_strjoin(envp[exp->idx], exp->eq + 1);
	else
	{
		tmp = ft_strjoin(exp->key, "=");
		joined = ft_strjoin(tmp, exp->eq + 1);
		free(tmp);
	}
	free(envp[exp->idx]);
	envp[exp->idx] = joined;
	free(exp->new_entry);
}

/**
 * @brief Replace an existing environment entry with a new export value.
 * @param envp Environment array containing the entry to replace.
 * @param exp Export context with the target index and new entry.
 * @return This function does not return a value.
 */
static void	handle_replace(char **envp, t_export *exp)
{
	free(envp[exp->idx]);
	envp[exp->idx] = exp->new_entry;
}

/**
 * @brief Apply the export update rules to an existing environment entry.
 * @param envp Environment array containing the matched key.
 * @param exp Export context with append or replace metadata.
 * @return This function does not return a value.
 */
void	update_existing_env(char **envp, t_export *exp)
{
	if (!exp->eq)
	{
		if (exp->new_entry)
			free(exp->new_entry);
		return ;
	}
	if (exp->append)
		handle_append(envp, exp);
	else
		handle_replace(envp, exp);
}

/**
 * @brief Process one export operand against the current shell environment.
 * @param arg Raw export operand.
 * @param state Shell state whose environment must be updated.
 * @return 0 on success, 1 when the identifier is invalid.
 */
int	process_export_arg(char *arg, t_shell_state *state)
{
	t_export	exp;

	ft_bzero(&exp, sizeof(exp));
	parse_export_arg(arg, &exp);
	if (!is_valid_ident(exp.key))
		return (report_invalid_identifier(arg, &exp));
	int	idx;

	idx = get_env_index(exp.key, state);
	if (idx != -1)
	{
		exp.idx = (size_t)idx;
		return (process_existing_export(&exp, &state->envp));
	}
	else
		return (process_new_export(&exp, &state->envp));
}
