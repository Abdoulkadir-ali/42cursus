/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 23:53:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "exit.h"
#include "gameplay.h"
#include <X11/keysym.h>

int	on_key_press(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	handle_key_press(keycode, &app->world->player.controller);
	if (keycode == XK_Escape)
		safe_exit(NULL, app, 0);
	return (0);
}

int	on_key_release(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	handle_key_release(keycode, &app->world->player.controller);
	return (0);
}

int	on_destroy(void *param)
{
	safe_exit(NULL, (t_app *)param, 0);
	return (0);
}
