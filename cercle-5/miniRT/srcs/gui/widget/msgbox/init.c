/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 10:46:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

t_widget	*widget_make_msgbox(const char *title, const char *msg,
		t_vec2i pos)
{
	t_widget	*w;

	w = widget_create(WIDGET_MESSAGE_BOX, pos, vec2i(320, 150), title);
	if (!w)
		return (NULL);
	if (msg)
		w->msg_text = ft_strdup(msg);
	w->visible = false;
	return (w);
}
