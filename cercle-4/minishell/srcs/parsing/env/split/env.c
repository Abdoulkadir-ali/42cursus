/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:02:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 05:01:22 by abdoali          ###   ########.fr       */
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
	/* Special-case shell-provided variables when not present in envp */
	if (ft_strlen(var_name) == 3 && ft_strncmp(var_name, "UID", 4) == 0)
		return (ft_itoa(getuid()));
	val = ft_calloc(1, 1);
	return (val);
}

char	*handle_dollar(char *str, int *i, char **envp, int status)
{
	char	var_name[256];
	int		j;
	char	*val;

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
	j = 0;
	if (ft_isdigit((unsigned char)str[*i]) && str[*i])
		var_name[j++] = str[(*i)++];
	else
		while (str[*i] && (ft_isalnum((unsigned char)str[*i]) || str[*i] == '_')
			&& j < 255)
			var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
	val = get_env_value(var_name, envp);
	return (val);
}
