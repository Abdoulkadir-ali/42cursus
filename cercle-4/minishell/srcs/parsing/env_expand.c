/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:59:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 16:10:00 by abdoali          ###   ########.fr       */
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

static char	*handle_dollar(char *str, int *i, char **envp, int exit_code)
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

char	*expand_string(char *str, char **envp, int exit_code)
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
		if (str[i] == '\\' && !qt[0] && str[i + 1])
		{
			i++;
			tmp = ft_substr(str, i, 1);
			append_chunk(&res, tmp);
			i++;
			continue ;
		}
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
		if (str[i] == '$')
		{
			// If $ is followed by a quote, another $, or not a valid var char, treat as literal
			if (str[i + 1] == '\'' || str[i + 1] == '$' || (!is_var_char(str[i + 1]) && str[i + 1] != '"' && str[i + 1] != '?'))
			{
				tmp = ft_substr(str, i, 1);
				append_chunk(&res, tmp);
				i++;
				continue ;
			}
			// Expand only if not in single quotes and followed by valid var char
			if (!qt[0] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
			{
				tmp = handle_dollar(str, &i, envp, exit_code);
				append_chunk(&res, tmp);
				continue ;
			}
		}
		tmp = ft_substr(str, i, 1);
		append_chunk(&res, tmp);
		i++;
	}
	return (res);
}

char	*expand_heredoc(char *str, char **envp, int exit_code)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?' || is_var_char(str[i + 1]))
			{
				tmp = handle_dollar(str, &i, envp, exit_code);
				append_chunk(&res, tmp);
				continue ;
			}
		}
		tmp = ft_substr(str, i, 1);
		append_chunk(&res, tmp);
		i++;
	}
	return (res);
}

void	expand_tokens(t_nodes **tokens, char **envp, int exit_code)
{
	t_nodes	*tmp;
	t_nodes	*prev;
	t_nodes	*next;
	t_token	*tok;
	char	*expanded;

	tmp = *tokens;
	prev = NULL;
	while (tmp)
	{
		tok = (t_token *)tmp->content;
		next = tmp->next;
		if (tok->type == TOKEN_WORD)
		{
			if (!tok->quoted && tok->value[0] == '~' && (tok->value[1] == '\0' || tok->value[1] == '/'))
			{
				char *home = get_env_value("HOME", envp);
				char *new_val = ft_strjoin(home, tok->value + 1);
				free(home);
				free(tok->value);
				tok->value = new_val;
			}
			expanded = expand_string(tok->value, envp, exit_code);
			if (expanded)
			{
				free(tok->value);
				tok->value = expanded;
			}
			if (!tok->quoted && ft_strchr(tok->value, ' '))
			{
				char **split = ft_split(tok->value, ' ');
				if (split)
				{
					t_nodes *new_list = NULL;
					int k = 0;
					while (split[k])
					{
						if (ft_strlen(split[k]) > 0)
						{
							t_token *new_tok = malloc(sizeof(t_token));
							new_tok->type = TOKEN_WORD;
							new_tok->value = ft_strdup(split[k]);
							new_tok->quoted = 0;
							ft_lstadd_back(&new_list, ft_lstnew(new_tok));
						}
						free(split[k]);
						k++;
					}
					free(split);
					if (new_list)
					{
						if (prev)
							prev->next = new_list;
						else
							*tokens = new_list;
						t_nodes *last = new_list;
						while (last->next) last = last->next;
						last->next = next;
						ft_lstdelone(tmp, del_token);
						tmp = last;
						continue;
					}
				}
			}
			// DEBUG PRINT
			if (ft_strlen(tok->value) == 0 && tok->quoted == 0)
			{
				t_nodes *del = tmp;
				tmp = next;
				if (prev)
					prev->next = next;
				else
					*tokens = next;
				ft_lstdelone(del, del_token);
				continue ;
			}
			// Wildcard Expansion Logic
			   if (!tok->quoted && ft_strchr(tok->value, '*'))
			   {
				   t_nodes *matches = expand_wildcard(tok->value);
				   if (matches)
				   {
					   t_nodes *new_nodes_head = NULL;
					   t_nodes *new_nodes_tail = NULL;
					   t_nodes *curr_match = matches;
					   while (curr_match)
					   {
						   t_token *new_tok = malloc(sizeof(t_token));
						   new_tok->type = TOKEN_WORD;
						   new_tok->value = ft_strdup(curr_match->content);
						   new_tok->quoted = 0;
						   t_nodes *new_node = ft_lstnew(new_tok);
						   if (!new_nodes_head)
							   new_nodes_head = new_node;
						   else
							   new_nodes_tail->next = new_node;
						   new_nodes_tail = new_node;
						   curr_match = curr_match->next;
					   }
					   ft_lstclear(&matches, free);

					   // Splice new nodes
					   if (prev)
						   prev->next = new_nodes_head;
					   else
						   *tokens = new_nodes_head;
					   new_nodes_tail->next = next;

					   // Free original node and update pointers
					   ft_lstdelone(tmp, del_token);
					   prev = new_nodes_tail;
					   tmp = next;
					   continue;
				   }
				   // If no matches, keep the original token as is
			   }
		}
		prev = tmp;
		tmp = next;
	}
}
