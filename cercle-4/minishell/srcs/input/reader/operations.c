/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 07:09:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 02:19:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Return the static table of continuation operators and delimiters.
 * @return Pointer to the static operator definition array.
 */
t_op_def	*get_ops(void)
{
	static t_op_def	ops[] = {
	{'\'', "'", "quote", '\''},
	{'"', "\"", "dquote", '"'},
	{'(', "(", "lparen", ')'},
	{')', ")", "rparen", '('},
	{'o', "||", "or", 0},
	{'a', "&&", "and", 0},
	{'|', "|", "pipe", 0},
	{'\\', "\\", "", 0},
	{0, NULL, NULL, 0}
	};

	return (ops);
}

/**
 * @brief Resolve one operator definition from its continuation code.
 * @param ops Operator definition table to search.
 * @param code Continuation code returned by the extender logic.
 * @return Pointer to the matching operator definition, or NULL.
 */
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
