/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:02:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Resolve one environment variable name into its string value.
 * @param var_name Variable name without the leading dollar sign.
 * @param envp Environment array used for lookup.
 * @return Newly allocated value string, possibly empty when undefined.
 */
char	*get_env_value(char *var_name, char **envp)
{
	char	*val;

	if (ft_strncmp(var_name, "UID", 4) == 0)
		return (ft_itoa(getuid()));
	val = ft_get_env(var_name, envp);
	if (val)
		return (ft_strdup(val));
	return (ft_calloc(1, 1));
}

/**
 * @brief Handle special dollar forms such as `$?` and `$$`.
 * @param str Source expansion string.
 * @param i Input cursor advanced in place.
 * @param status Last shell exit status.
 * @return Newly allocated replacement string, or NULL for normal variables.
 */
static char	*handle_special_dollar(char *str, int *i, int status)
{
	(*i)++;
	if (!str[*i])
		return (ft_strdup("$"));
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(status));
	}
	if (str[*i] == '$')
	{
		(*i)++;
		return (ft_itoa(getpid()));
	}
	return (NULL);
}

/**
 * @brief Parse a variable name after `$` and return its resolved value.
 * @param str Source expansion string.
 * @param i Input cursor advanced in place.
 * @param envp Environment array used for lookup.
 * @return Newly allocated value string.
 */
static char	*handle_var_name(char *str, int *i, char **envp)
{
	char	var_name[256];
	int		j;

	j = 0;
	if (ft_isdigit((unsigned char)str[*i]) && str[*i])
		var_name[j++] = str[(*i)++];
	else
		while (str[*i] && (ft_isalnum((unsigned char)str[*i]) || str[*i] == '_')
			&& j < 255)
			var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
	return (get_env_value(var_name, envp));
}

/**
 * @brief Expand one dollar-prefixed expression into its resolved value.
 * @param str Source expansion string.
 * @param i Input cursor advanced in place.
 * @param envp Environment array used for lookup.
 * @param status Last shell exit status.
 * @return Newly allocated replacement string.
 */
char	*handle_dollar(char *str, int *i, char **envp, int status)
{
	char	*val;

	val = handle_special_dollar(str, i, status);
	if (val)
		return (val);
	return (handle_var_name(str, i, envp));
}
