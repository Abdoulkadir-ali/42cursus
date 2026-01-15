/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:02:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 02:16:55 by abdoali          ###   ########.fr       */
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
	val = ft_calloc(1, 1);
	return (val);
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*handle_dollar(char *str, int *i, char **envp, int exit_code)
{
	int		start;
	char	*var_name;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(exit_code));
	}
	if (!is_var_char(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	value = get_env_value(var_name, envp);
	free(var_name);
	return (value);
}

void	append_chunk(char **res, char *chunk)
{
	char	*tmp;

	if (!chunk)
		return ;
	if (!*res)
		*res = chunk;
	else
	{
		tmp = ft_strjoin(*res, chunk);
		free(*res);
		free(chunk);
		*res = tmp;
	}
}
