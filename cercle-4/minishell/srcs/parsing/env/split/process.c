/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:46:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	flush_token(t_exp_buffers *buf)
{
	if (buf->word && *buf->word)
	{
		add_token_node(&buf->head, &buf->tail, buf->word, 0);
		buf->word = NULL;
	}
}

static void	append_char_to_target(t_exp_buffers *buf, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	if (buf->expanded)
		append_chunk(&buf->expanded, ft_strdup(tmp));
	else
		append_chunk(&buf->word, ft_strdup(tmp));
}

void	process_val_split(char *val, t_exp_buffers *buf)
{
	int	k;

	if (!val || !*val)
		return ;
	k = 0;
	while (val[k])
	{
		if (ft_isspace((unsigned char)val[k]))
			flush_token(buf);
		else
			append_char_to_target(buf, val[k]);
		k++;
	}
}
