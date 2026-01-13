/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:38:26 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 22:46:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	print_token(FILE *f, t_token *dtok)
{
	if (dtok)
	{
		if (dtok->value)
			fprintf(f, "type=%d quoted=%d expanded=%d val='%s'\n", dtok->type,
				dtok->quoted, dtok->expanded, dtok->value);
		else
			fprintf(f, "type=%d quoted=%d expanded=%d val='(null)'\n",
				dtok->type, dtok->quoted, dtok->expanded);
	}
	else
		fprintf(f, "<null token>\n");
}

int	debug_dump_tokens_and_consume(t_nodes **ptokens)
{
	FILE	*f;
	t_nodes	*cur;
	t_token	*tok;

	if (!getenv("MINI_DEBUG_TOK"))
		return (0);
	f = fopen("log/expand_debug.txt", "a");
	if (!f)
		return (0);
	fprintf(f, "-- debug tokens --\n");
	cur = *ptokens;
	while (cur)
	{
		tok = (t_token *)cur->content;
		if (tok && tok->value)
			fprintf(f, "type=%d quoted=%d expanded=%d val='%s'\n", tok->type,
				tok->quoted, tok->expanded, tok->value);
		else
			fprintf(f, "<null token>\n");
		cur = cur->next;
	}
	fprintf(f, "-- end debug --\n\n");
	fclose(f);
	ft_lstclear(ptokens, del_token);
	return (1);
}

void	debug_dump_segment(t_nodes *segment)
{
	FILE	*f;
	t_nodes	*dbg;

	if (!getenv("MINI_DEBUG_CMD"))
		return ;
	f = fopen("log/exec_debug.txt", "a");
	if (!f)
		return ;
	fprintf(f, "-- segment tokens --\n");
	dbg = segment;
	while (dbg)
	{
		print_token(f, (t_token *)dbg->content);
		dbg = dbg->next;
	}
	fprintf(f, "-- end segment --\n\n");
	fclose(f);
}
