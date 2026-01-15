/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:24:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_nodes	*expand_and_split(char *str, char **envp, int exit_code)
{
	t_exp_ctx	ctx;
	t_locals	locals;

	if (!str)
		return (NULL);
	locals.head = NULL;
	locals.tail = NULL;
	locals.curr = NULL;
	locals.i = 0;
	locals.qt[0] = 0;
	locals.qt[1] = 0;
	locals.wd_quoted = 0;
	init_exp_ctx(&ctx, str, envp, exit_code);
	ctx.state.i = &locals.i;
	ctx.state.qt = locals.qt;
	ctx.state.wd_quoted = &locals.wd_quoted;
	ctx.state.curr = &locals.curr;
	ctx.lists.head = &locals.head;
	ctx.lists.tail = &locals.tail;
	run_expansion_loop(&ctx);
	return (finalize_expansion(&ctx));
}
