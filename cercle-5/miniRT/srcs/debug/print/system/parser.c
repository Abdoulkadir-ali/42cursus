/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "parser.h"

void	print_parser(t_parser *p)
{
	const char	*eof_str;

	if (!p)
		return ;
	eof_str = "false";
	if (p->eof)
		eof_str = "true";
	printf("parser(\n  fd: %d\n  cursor: %zu\n", p->fd, p->cursor);
	printf("  bytes_read: %zu\n  eof: %s\n)", p->bytes_read, eof_str);
}
