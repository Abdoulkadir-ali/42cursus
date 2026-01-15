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

static void	flush_token(t_exp_output *out)
{
	if (out->word && *out->word)
	{
		add_token_node(&out->head, &out->tail, out->word, 0);
		out->word = NULL;
	}
}

void	process_val_split(char *val, t_exp_output *out)
{
	int	k;

	if (!val || !*val)
		return ;
	k = 0;
	while (val[k])
	{
		if (ft_isspace((unsigned char)val[k]))
			flush_token(out);
		else
			exp_push_char(out, val[k]);
		k++;
	}
}
