/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:41:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 05:49:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Check whether an input line contains only whitespace.
 * @param str Raw input line.
 * @return 1 when the line is empty after whitespace filtering, else 0.
 */
int	is_whitespace_only(char *str)
{
	while (str && *str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

/**
 * @brief Detach tokens from the current cursor until a semicolon is reached.
 * @param segment Output slot receiving the extracted segment head.
 * @param seg_tail Output slot receiving the extracted segment tail.
 * @param it Cursor advanced to the semicolon or stream end.
 * @return This function does not return a value.
 */
void	build_segment_until_semicolon(t_nodes **segment, t_nodes **seg_tail,
		t_nodes **it)
{
	t_nodes	*next;

	while (*it && !cmp_node_type(*it, TOKEN_SEMICOLON))
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

/**
 * @brief Remove one semicolon token and expose the next segment cursor.
 * @param it Current token node after segment extraction.
 * @param pnext Output slot receiving the next segment start.
 * @return This function does not return a value.
 */
void	consume_semicolon_if_present(t_nodes *it, t_nodes **pnext)
{
	if (cmp_node_type(it, TOKEN_SEMICOLON))
	{
		*pnext = it->next;
		del_token(it->content);
		free(it);
	}
	else
		*pnext = it;
}
