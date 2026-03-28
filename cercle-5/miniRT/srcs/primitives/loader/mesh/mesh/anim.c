/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 08:21:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

bool	scene_add_animated(t_scene *scene, t_skinned_mesh animated)
{
    if (!DYNARRAY_ENSURE_INT(&scene->animated, &scene->anim_count,
            &scene->anim_cap, sizeof(t_skinned_mesh)))
        return (false);
    scene->animated[scene->anim_count++] = animated;
    return (true);
}

bool	scene_add_clip(t_scene *scene, t_animation anim)
{
    if (!DYNARRAY_ENSURE_INT(&scene->clips, &scene->clip_count,
            &scene->clip_cap, sizeof(t_animation)))
        return (false);
    scene->clips[scene->clip_count++] = anim;
    return (true);
}

bool	scene_add_animation(t_scene *scene, t_animation anim)
{
    return (scene_add_clip(scene, anim));
}
