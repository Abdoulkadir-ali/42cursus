/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:51:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	scene_init(t_scene *s)
{
	memset(s, 0, sizeof(*s));
	s->cap_lights = 4;
	s->cap_bvh = 64;
	s->cap_planes = 8;
	s->cap_textures = 8;
	s->cap_bhs = 4;
	s->lights = (t_light *)malloc(sizeof(t_light) * s->cap_lights);
	s->bvh_objs = (t_object *)malloc(sizeof(t_object) * s->cap_bvh);
	s->planes = (t_object *)malloc(sizeof(t_object) * s->cap_planes);
	s->textures = (t_texture *)calloc(s->cap_textures, sizeof(t_texture));
	s->bhs = (t_blackhole *)malloc(sizeof(t_blackhole) * s->cap_bhs);
	if (!s->lights || !s->bvh_objs || !s->planes || !s->textures || !s->bhs)
		return (-1);
	s->gravity = v3(0.0f, -9.81f, 0.0f);
	s->next_group_id = 1;
	return (0);
}
