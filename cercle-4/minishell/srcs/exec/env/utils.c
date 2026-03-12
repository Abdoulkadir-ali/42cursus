/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:46:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:22:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Count the number of entries stored in an environment array.
 * @param envp NULL-terminated environment array.
 * @return Number of non-NULL entries.
 */
size_t	count_env(char **envp)
{
	size_t	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

/**
 * @brief Validate a shell identifier used by export or unset.
 * @param str Candidate identifier string.
 * @return True when the identifier is valid, else false.
 */
bool	is_valid_ident(char *str)
{
	size_t	i;

	if (!str || !str[0])
		return (false);
	i = 0;
	if (!ft_isalpha((unsigned char)str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum((unsigned char)str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Split one export operand into the key and provisional entry fields.
 * @param arg Raw export operand.
 * @param exp Export parsing context updated in place.
 * @return This function does not return a value.
 */
static void	set_key_and_entry(char *arg, t_export *exp)
{
	if (exp->append)
		exp->key = ft_substr(arg, 0, exp->eq - arg - 1);
	else
		exp->key = ft_substr(arg, 0, exp->eq - arg);
	exp->new_entry = ft_strdup(arg);
}

/**
 * @brief Parse one export operand into the reusable export context.
 * @param arg Raw export operand.
 * @param exp Export parsing context updated in place.
 * @return This function does not return a value.
 */
void	parse_export_arg(char *arg, t_export *exp)
{
	exp->eq = ft_strchr(arg, '=');
	exp->append = false;
	if (exp->eq)
	{
		if (exp->eq > arg && *(exp->eq - 1) == '+')
			exp->append = true;
		set_key_and_entry(arg, exp);
	}
	else
	{
		exp->key = ft_strdup(arg);
		exp->new_entry = ft_strjoin(exp->key, "=");
	}
}

/**
 * @brief Report an invalid export identifier and release parsed resources.
 * @param arg Raw operand that failed validation.
 * @param exp Export parsing context holding allocated members.
 * @return Always returns 1.
 */
int	report_invalid_identifier(char *arg, t_export *exp)
{
	ft_puterror("export: `%s': not a valid identifier\n", arg);
	free(exp->key);
	if (exp->new_entry)
		free(exp->new_entry);
	return (1);
}
