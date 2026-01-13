/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:27:39 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 22:55:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	initialize_segment_builder(t_nodes **segment, t_nodes **seg_tail,
		t_nodes **it, t_nodes *cursor)
{
	*segment = NULL;
	*seg_tail = NULL;
	*it = cursor;
}

void	build_segment_until_semicolon(t_nodes **segment, t_nodes **seg_tail,
		t_nodes **it)
{
	t_nodes	*next;

	while (*it && ((t_token *)(*it)->content)->type != TOKEN_SEMICOLON)
	{
		next = (*it)->next;
		(*it)->next = NULL;
		if (!*segment)
			*segment = *it;
		else
			(*seg_tail)->next = *it;
		*seg_tail = *it;
		*it = next;
	}
}

void	consume_semicolon_if_present(t_nodes *it, t_nodes **pnext)
{
	if (it && ((t_token *)it->content)->type == TOKEN_SEMICOLON)
	{
		*pnext = it->next;
		del_token(it->content);
		free(it);
	}
	else
		*pnext = it;
}
