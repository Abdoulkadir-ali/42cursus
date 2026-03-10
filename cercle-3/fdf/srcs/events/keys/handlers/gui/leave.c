/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:25:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:24:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Exit the application in response to the escape key.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the runtime resources.
 * @return Result of `cleanup_and_exit`.
 */
int	handle_escape(int keycode, t_events *events)
{
	(void)keycode;
	return (cleanup_and_exit(events));
}
