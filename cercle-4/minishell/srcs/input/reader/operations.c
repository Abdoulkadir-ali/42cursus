/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 07:09:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/25 22:21:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_op_def	*get_ops(void)
{
	static t_op_def	ops[] = {
	{'\'', "'", "quote", '\''},
	{'"', "\"", "dquote", '"'},
	{'(', "(", "lparen", ')'},
	{')', ")", "rparen", '('},
	{'|', "|", "pipe", 0},
	{'o', "||", "or", 0},
	{'a', "&&", "and", 0},
	{'\\', "\\", "", 0},
	{0, NULL, NULL, 0}
	};

	return (ops);
}

t_op_def	*ext_get_op_def(t_op_def *ops, char code)
{
	int	i;

	i = 0;
	while (ops[i].code)
	{
		if (ops[i].code == code)
			return (&ops[i]);
		i++;
	}
	return (NULL);
}
