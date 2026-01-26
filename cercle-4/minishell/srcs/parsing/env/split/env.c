/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:02:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:20:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	int		len;
	char	*val;

	i = 0;
	len = ft_strlen(var_name);
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	if (ft_strlen(var_name) == 3 && ft_strncmp(var_name, "UID", 4) == 0)
		return (ft_itoa(getuid()));
	val = ft_calloc(1, 1);
	return (val);
}

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

char	*handle_dollar(char *str, int *i, char **envp, int status)
{
	char	*val;

	val = handle_special_dollar(str, i, status);
	if (val)
		return (val);
	return (handle_var_name(str, i, envp));
}
