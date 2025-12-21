/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:53:06 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 18:28:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	setup_hooks(t_events *e)
{
	mlx_hook(e->window->ptr, 17, 0, cleanup_and_exit, e);
	mlx_hook(e->window->ptr, 4, 1L << 2, mouse_press, e);
	mlx_hook(e->window->ptr, 5, 1L << 3, mouse_release, e);
	mlx_hook(e->window->ptr, 6, 1L << 6, mouse_move, e);
	mlx_hook(e->window->ptr, 2, 1L << 0, key_press, e);
	mlx_hook(e->window->ptr, 3, 1L << 1, key_release, e);
	mlx_hook(e->window->ptr, 22, 1L << 17, handle_resize, e);
	mlx_loop_hook(e->window->mlx_ptr, loop_hook, e);
}

void	init_mouse(t_mouse *mouse)
{
	mouse->left_pressed = 0;
	mouse->right_pressed = 0;
	mouse->middle_pressed = 0;
	mouse->last_x = 0;
	mouse->last_y = 0;
	mouse->middle_start_x = 0;
	mouse->middle_start_y = 0;
}

void	init_keys(t_keys *keys)
{
	keys->up = 0;
	keys->down = 0;
	keys->left = 0;
	keys->right = 0;
	keys->ctrl_left = 0;
	keys->ctrl_right = 0;
	keys->shift_left = 0;
	keys->shift_right = 0;
	keys->l = 0;
	keys->z = 0;
	keys->f = 0;
	keys->h = 0;
	keys->d = 0;
	keys->t = 0;
	keys->s = 0;
	keys->a = 0;
	keys->x = 0;
	keys->i = 0;
	keys->v = 0;
	keys->g = 0;
}

static void	init_events_graphics(t_events *e)
{
	if (e->graphics)
	{
		e->render_mode = e->graphics->render_config.render_mode;
		e->lod_value = e->graphics->render_config.lod_value;
		e->use_depth_culling = e->graphics->render_config.use_depth_culling;
		e->fill_triangles = e->graphics->render_config.fill_triangles;
	}
	else
	{
		e->render_mode = 0;
		e->lod_value = DEFAULT_LOD_LEVEL;
		e->use_depth_culling = 1;
		e->fill_triangles = 0;
	}
}

t_events	*init_events(t_events_args *args)
{
	t_events	*e;

	e = malloc(sizeof(t_events));
	if (!e)
		return (NULL);
	e->window = args->window;
	e->graphics = args->graphics;
	e->gui = *args->gui;
	e->camera_manager = args->camera_manager;
	if (args->camera_manager)
		e->camera = args->camera_manager->camera;
	else
		e->camera = NULL;
	e->maps = args->maps;
	e->map = args->map;
	init_events_graphics(e);
	init_mouse(&e->mouse);
	init_keys(&e->keys);
	set_key_actions(&e->key_maps);
	set_key_releases(&e->key_maps);
	return (e);
}
