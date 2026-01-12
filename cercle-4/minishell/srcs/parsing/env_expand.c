/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:59:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/12 02:58:44 by abdoali          ###   ########.fr       */
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

static void	add_token_node(t_nodes **head, t_nodes **tail, char *val, int quoted)
{
	t_token	*tok;
	t_nodes	*node;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return ;
	tok->type = TOKEN_WORD;
	tok->value = val;
	tok->quoted = quoted;
	tok->expanded = 1;
	node = ft_lstnew(tok);
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
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
			if (qt[1] && str[i + 1] != '$' && str[i + 1] != '"'
				&& str[i + 1] != '\\' && str[i + 1] != '\n')
			{
				tmp = ft_substr(str, i, 1);
				append_chunk(&res, tmp);
				i++;
				continue ;
			}
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
		if (str[i] == '$' && !qt[0] && !qt[1] && (str[i + 1] == '\'' || str[i + 1] == '"'))
		{
			i++;
			continue ;
		}
		if (str[i] == '$')
		{
			if (str[i + 1] == '\'' || str[i + 1] == '$' || (!is_var_char(str[i + 1]) && str[i + 1] != '"' && str[i + 1] != '?'))
			{
				tmp = ft_substr(str, i, 1);
				append_chunk(&res, tmp);
				i++;
				continue ;
			}
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

static t_nodes	*expand_and_split(char *str, char **envp, int exit_code)
{
	t_nodes	*head;
	t_nodes	*tail;
	char	*curr;
	int		i;
	int		qt[2];
	int		wd_quoted;
	char	*tmp;

	head = NULL;
	tail = NULL;
	curr = NULL;
	i = 0;
	qt[0] = 0;
	qt[1] = 0;
	wd_quoted = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		// Quote Toggling
		if (str[i] == '\'' && !qt[1])
		{
			qt[0] = !qt[0];
			wd_quoted = 1;
			if (!curr) curr = ft_strdup("");
			i++;
			continue ;
		}
		if (str[i] == '"' && !qt[0])
		{
			qt[1] = !qt[1];
			wd_quoted = 1;
			if (!curr) curr = ft_strdup("");
			i++;
			continue ;
		}
		// Escape handling
		if (str[i] == '\\' && !qt[0])
		{
			if (qt[1] && str[i+1] != '$' && str[i+1] != '"' && str[i+1] != '\\' && str[i+1] != '\n')
			{
				tmp = ft_substr(str, i, 1);
				append_chunk(&curr, tmp);
				i++; // keep backslash literal
			}
			else
			{
				i++; // skip backslash
				if (str[i])
				{
					tmp = ft_substr(str, i, 1);
					append_chunk(&curr, tmp);
					wd_quoted = 1; // Escaped char is quoted
					i++;
				}
			}
			continue ;
		}
		// Dollar Expansion
		if (str[i] == '$')
		{
			if ((str[i + 1] == '\'' || str[i + 1] == '"') && !qt[0] && !qt[1])
			{
				i++; // Skip $ followed by quotes if unquoted
				continue ;
			}
			if ((!is_var_char(str[i + 1]) && str[i + 1] != '?') || qt[0] || (str[i+1] == '"' && qt[1]))
			{
				// Literal $ (invalid var char, or single quotes, or "$"" case?)
				// Wait, "$"" -> $ is valid? Bash "$""" -> $.
				// My logic: append literal.
				tmp = ft_substr(str, i, 1);
				append_chunk(&curr, tmp);
				i++;
				continue ;
			}
			char *val = handle_dollar(str, &i, envp, exit_code);
			if (qt[1])
			{
				append_chunk(&curr, val);
				wd_quoted = 1;
			}
			else
			{
				int k = 0;
				if (!val || !*val) { free(val); continue; } // Empty expansion
				while (val[k])
				{
					if (ft_isspace(val[k]))
					{
						if (curr)
						{
							add_token_node(&head, &tail, curr, wd_quoted);
							curr = NULL;
							wd_quoted = 0;
						}
					}
					else
					{
						char buf[2] = {val[k], 0};
						append_chunk(&curr, ft_strdup(buf));
					/* appended from unquoted variable expansion -> mark as unquoted */
					wd_quoted = 0;
					}
					k++;
				}
				free(val);
			}
			continue ;
		}
		// Literal Char
		tmp = ft_substr(str, i, 1);
		append_chunk(&curr, tmp);
		/* if this literal was appended outside any quotes, mark token as containing unquoted chars */
		if (!qt[0] && !qt[1])
			wd_quoted = 0;
		i++;
	}
	if (curr)
		add_token_node(&head, &tail, curr, wd_quoted);
	else if (wd_quoted) // Case ""
		add_token_node(&head, &tail, ft_strdup(""), 1);
	
	return (head);
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
	t_nodes	*new_head;
	t_nodes	*new_tail;
	t_nodes	*curr;
	t_nodes	*next_node;
	t_token	*tok;
	t_nodes	*prev;

	new_head = NULL;
	new_tail = NULL;
	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		next_node = curr->next;
		tok = (t_token *)curr->content;
		if (tok->type == TOKEN_WORD)
		{
			// If this WORD is the argument of a heredoc redirection (previous token is TOKEN_HEREDOC),
			// do not perform expansion/splitting here. Keep the original token (preserve quoting).
			if (prev && ((t_token *)prev->content)->type == TOKEN_HEREDOC)
			{
				if (!new_head) new_head = curr;
				else new_tail->next = curr;
				new_tail = curr;
				curr->next = NULL;
				prev = new_tail;
				curr = next_node;
				continue;
			}
			// Tilde Expansion
			if (!tok->quoted && tok->value[0] == '~' && (tok->value[1] == '\0' || tok->value[1] == '/'))
			{
				char *home = get_env_value("HOME", envp);
				char *new_val = ft_strjoin(home, tok->value + 1);
				free(home);
				free(tok->value);
				tok->value = new_val;
			}

			// Variable Splitting & Expansion
			t_nodes *expanded_list = expand_and_split(tok->value, envp, exit_code);
			
			// Process expanded tokens (Wildcards)
			t_nodes *exp_curr = expanded_list;
			while (exp_curr)
			{
				t_nodes *exp_next = exp_curr->next;
				t_token *exp_tok = (t_token *)exp_curr->content;

				/* Ensure expanded items remain words: do not reclassify expansions
				   (e.g. an expansion that produces ">>" must stay a WORD). */
				exp_tok->type = TOKEN_WORD;
				
				// Wildcard Check
				if (!exp_tok->quoted && ft_strchr(exp_tok->value, '*'))
				{
					t_nodes *matches = expand_wildcard(exp_tok->value);
					if (matches)
					{
						/* If this wildcard is the target of a redirection and yields multiple matches,
						   it's an ambiguous redirect. Report error and keep literal. */
						int is_redir_target = 0;
						if (prev)
						{
							t_token *prev_tok = (t_token *)prev->content;
							if (prev_tok->type == TOKEN_RED_OUT || prev_tok->type == TOKEN_APPEND || prev_tok->type == TOKEN_RED_IN)
								is_redir_target = 1;
						}
						if (is_redir_target)
						{
							int mcount = 0;
							t_nodes *mc = matches;
							while (mc) { mcount++; mc = mc->next; }
							if (mcount > 1)
							{
								ft_putstr_fd("minishell: ", 2);
								ft_putstr_fd(exp_tok->value, 2);
								ft_putendl_fd(": ambiguous redirect", 2);
								extern int g_exit_code;
								g_exit_code = 1;
								/* cleanup matches and keep literal token instead */
								while (matches)
								{
									t_nodes *tmp_m = matches->next;
									free(matches->content);
									free(matches);
									matches = tmp_m;
								}
								/* keep literal: fall through to attach exp_curr below */
							}
						}
						/* if not ambiguous, or after cleanup, proceed to insert matches */
						// Insert matches
						t_nodes *m_curr = matches;
						while (m_curr)
						{
							t_token *new_tok = malloc(sizeof(t_token));
							new_tok->type = TOKEN_WORD;
							new_tok->value = ft_strdup((char *)m_curr->content);
							new_tok->quoted = 0; // Expanded wildcards are unquoted words
							new_tok->expanded = 1;
							
							t_nodes *mnode = ft_lstnew(new_tok);
							if (!new_head) new_head = mnode;
							else new_tail->next = mnode;
							new_tail = mnode;
							
							m_curr = m_curr->next;
						}
						// Cleanup matches list (char * content)
						t_nodes *tmp_m;
						m_curr = matches;
						while (m_curr)
						{
							tmp_m = m_curr->next;
							free(m_curr->content);
							free(m_curr);
							m_curr = tmp_m;
						}
						// Consume exp_curr (don't add to list)
						del_token(exp_curr->content);
						free(exp_curr);
					}
					else
					{
						// No matches: keep literal
						if (!new_head) new_head = exp_curr;
						else new_tail->next = exp_curr;
						new_tail = exp_curr;
						exp_curr->next = NULL; 
					}
				}
				else
				{
					// No wildcard or quoted: keep
					if (!new_head) new_head = exp_curr;
					else new_tail->next = exp_curr;
					new_tail = exp_curr;
					exp_curr->next = NULL;
				}
				exp_curr = exp_next;
			}
			
			// Free original node logic
			del_token(curr->content);
			free(curr);
		}
		else
		{
			// Non-WORD: keep as is
			if (!new_head) new_head = curr;
			else new_tail->next = curr;
			new_tail = curr;
			curr->next = NULL;
			prev = new_tail;
		}
		curr = next_node;
		if (prev == NULL && new_tail)
			prev = new_tail;
	}
	*tokens = new_head;
}
