/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:59:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 05:34:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*get_env_value(char *var_name, char **envp)
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

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*handle_dollar(char *str, int *i, char **envp)
{
	int		start;
	char	*var_name;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(0)); // Placeholder for exit code
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

static void	append_chunk(char **res, char *chunk)
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

static char	*expand_string(char *str, char **envp)
{
	char	*res;
	char	*tmp;
	int		i;
	int		qt[2]; // 0=single, 1=double

	i = 0;
	qt[0] = 0;
	qt[1] = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'' && !qt[1])
		{
			qt[0] = !qt[0];
			i++;
			continue ;
		}
		if (str[i] == '"' && !qt[0])
		{
			qt[1] = !qt[1];
			i++;
			continue ;
		}
		if (str[i] == '$' && !qt[0] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			tmp = handle_dollar(str, &i, envp);
			append_chunk(&res, tmp);
			continue ;
		}
		tmp = ft_substr(str, i, 1);
		append_chunk(&res, tmp);
		i++;
	}
	return (res);
}

void	expand_tokens(t_nodes *tokens, char **envp)
{
	t_nodes	*tmp;
	t_token	*tok;
	char	*expanded;

	tmp = tokens;
	while (tmp)
	{
		tok = (t_token *)tmp->content;
		if (tok->type == TOKEN_WORD)
		{
			expanded = expand_string(tok->value, envp);
			if (expanded)
			{
				free(tok->value);
				tok->value = expanded;
			}
		}
		tmp = tmp->next;
	}
}
