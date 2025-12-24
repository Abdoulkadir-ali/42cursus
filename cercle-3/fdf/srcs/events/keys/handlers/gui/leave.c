/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:25:31 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 15:17:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	handle_escape(int keycode, t_events *events)
{
	(void)keycode;
	return (cleanup_and_exit(events));
}
