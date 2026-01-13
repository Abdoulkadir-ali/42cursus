/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:53:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 03:56:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	debug_dump_tokens_and_consume(t_nodes **ptokens)
{
	FILE	*f;
	t_nodes	*cur;
	t_token	*tok;

	if (!getenv("MINI_DEBUG_TOK"))
		return (0);
	f = fopen("log/expand_debug.txt", "a");
	cur = *ptokens;
	if (f)
	{
		fprintf(f, "-- debug tokens --\n");
		while (cur)
		{
			tok = (t_token *)cur->content;
			if (tok && tok->value)
				fprintf(f, "type=%d quoted=%d expanded=%d val='%s'\n",
					tok->type, tok->quoted, tok->expanded, tok->value);
			else
				fprintf(f, "<null token>\n");
			cur = cur->next;
		}
		fprintf(f, "-- end debug --\n\n");
		fclose(f);
	}
	ft_lstclear(ptokens, del_token);
	return (1);
}

int	check_syntax_and_consume(t_nodes *tokens, int *exit_code)
{
	if (!check_syntax(tokens))
		return (0);
	consume_heredocs(tokens);
	*exit_code = 2;
	ft_lstclear(&tokens, del_token);
	return (1);
}

t_nodes	*extract_segment(t_nodes *cursor, t_nodes **pnext)
{
	t_nodes	*segment;
	t_nodes	*seg_tail;
	t_nodes	*it;
	t_nodes	*next;

	segment = NULL;
	seg_tail = NULL;
	it = cursor;
	while (it && ((t_token *)it->content)->type != TOKEN_SEMICOLON)
	{
		next = it->next;
		it->next = NULL;
		if (!segment)
			segment = it;
		else
			seg_tail->next = it;
		seg_tail = it;
		it = next;
	}
	if (it && ((t_token *)it->content)->type == TOKEN_SEMICOLON)
	{
		*pnext = it->next;
		del_token(it->content);
		free(it);
	}
	else
		*pnext = it;
	return (segment);
}

void	debug_dump_segment(t_nodes *segment)
{
	FILE	*f;
	t_nodes	*dbg;
	t_token	*dtok;

	if (!getenv("MINI_DEBUG_CMD"))
		return ;
	f = fopen("log/exec_debug.txt", "a");
	dbg = segment;
	if (!f)
		return ;
	fprintf(f, "-- segment tokens --\n");
	while (dbg)
	{
		dtok = (t_token *)dbg->content;
		if (dtok)
			fprintf(f, "type=%d quoted=%d expanded=%d val='%s'\n", dtok->type,
				dtok->quoted, dtok->expanded, dtok->value ? dtok->value : "");
		else
			fprintf(f, "<null token>\n");
		dbg = dbg->next;
	}
	fprintf(f, "-- end segment --\n\n");
	fclose(f);
}

int	try_handle_assignment_local(t_nodes *segment, char ***envp, int *exit_code)
{
	t_token	*first_tok;
	char	*eq;
	int		valid;
	char	*k;
	char	*key;
	char	*val;

	first_tok = (t_token *)segment->content;
	if (!first_tok || first_tok->type != TOKEN_WORD)
		return (0);
	eq = ft_strchr(first_tok->value, '=');
	if (!eq || eq == first_tok->value)
		return (0);
	valid = 1;
	k = first_tok->value;
	if (!ft_isalpha((unsigned char)k[0]) && k[0] != '_')
		valid = 0;
	for (char *p = k; *p && *p != '=' && valid; p++)
	{
		if (!ft_isalnum((unsigned char)*p) && *p != '_')
			valid = 0;
	}
	if (!valid || segment->next)
		return (0);
	key = ft_substr(first_tok->value, 0, eq - first_tok->value);
	val = ft_strdup(eq + 1);
	ft_set_env(key, val, envp);
	free(key);
	free(val);
	*exit_code = 0;
	ft_lstclear(&segment, del_token);
	return (1);
}
