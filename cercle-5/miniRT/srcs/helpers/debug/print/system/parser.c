/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_parser(t_parser *p)
{
	const char	*eof_str;

	if (!p)
		return ;
	eof_str = "false";
	if (p->eof)
		eof_str = "true";
	ft_print_debug("parser(\n  fd: %d\n  cursor: %zu\n", p->fd, p->cursor);
	ft_print_debug("  bytes_read: %zu\n  eof: %s\n)", p->bytes_read, eof_str);
}
