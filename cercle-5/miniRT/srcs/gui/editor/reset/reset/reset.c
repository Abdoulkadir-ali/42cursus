/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "editor.h"

static voidreset_cam_ctrl(t_gui *gui)
{
t_vec3f;

gui->cam_ctrl.camera = &gui->scene->camera;
gui->cam_ctrl.transform = gui->scene->camera.transform;
f = gui->scene->camera.transform.forward;
gui->cam_ctrl.target_rot.yaw = atan2(f.x, f.z);
gui->cam_ctrl.target_rot.pitch = asin(f.y);
gui->cam_ctrl.target_pos = gui->scene->camera.transform.pos;
gui->cam_ctrl.target_fov = gui->scene->camera.fov;
}

static voidrestore_prim_soa(t_primitive_array *d, const t_primitive_array *s)
{
size_tn;

n = s->count;
ft_memcpy(d->types, s->types, n * sizeof(uint8_t));
ft_memcpy(d->px, s->px, n * sizeof(float));
ft_memcpy(d->py, s->py, n * sizeof(float));
ft_memcpy(d->pz, s->pz, n * sizeof(float));
ft_memcpy(d->ax, s->ax, n * sizeof(float));
ft_memcpy(d->ay, s->ay, n * sizeof(float));
ft_memcpy(d->az, s->az, n * sizeof(float));
ft_memcpy(d->tx, s->tx, n * sizeof(float));
ft_memcpy(d->ty, s->ty, n * sizeof(float));
ft_memcpy(d->tz, s->tz, n * sizeof(float));
ft_memcpy(d->radii, s->radii, n * sizeof(float));
ft_memcpy(d->heights, s->heights, n * sizeof(float));
ft_memcpy(d->ex, s->ex, n * sizeof(float));
ft_memcpy(d->ey, s->ey, n * sizeof(float));
ft_memcpy(d->ez, s->ez, n * sizeof(float));
ft_memcpy(d->mat_ids, s->mat_ids, n * sizeof(uint16_t));
ft_memcpy(d->is_static, s->is_static, n * sizeof(uint8_t));
ft_memcpy(d->has_phys, s->has_phys, n * sizeof(uint8_t));
ft_memcpy(d->abb_min_x, s->abb_min_x, n * sizeof(float));
ft_memcpy(d->abb_min_y, s->abb_min_y, n * sizeof(float));
ft_memcpy(d->abb_min_z, s->abb_min_z, n * sizeof(float));
ft_memcpy(d->abb_max_x, s->abb_max_x, n * sizeof(float));
ft_memcpy(d->abb_max_y, s->abb_max_y, n * sizeof(float));
ft_memcpy(d->abb_max_z, s->abb_max_z, n * sizeof(float));
ft_memcpy(d->phys_idx, s->phys_idx, n * sizeof(int));
d->count = n;
}

static voidrestore_tri_soa(t_tri_array *d, const t_tri_array *s)
{
size_tn;
inti;

n = s->count;
i = 0;
while (i < 3)
{
ft_memcpy(d->vx[i], s->vx[i], n * sizeof(float));
ft_memcpy(d->vy[i], s->vy[i], n * sizeof(float));
ft_memcpy(d->vz[i], s->vz[i], n * sizeof(float));
i++;
}
i = 0;
while (i < 2)
{
ft_memcpy(d->ex[i], s->ex[i], n * sizeof(float));
ft_memcpy(d->ey[i], s->ey[i], n * sizeof(float));
ft_memcpy(d->ez[i], s->ez[i], n * sizeof(float));
i++;
}
ft_memcpy(d->nx, s->nx, n * sizeof(float));
ft_memcpy(d->ny, s->ny, n * sizeof(float));
ft_memcpy(d->nz, s->nz, n * sizeof(float));
ft_memcpy(d->tx, s->tx, n * sizeof(float));
ft_memcpy(d->ty, s->ty, n * sizeof(float));
ft_memcpy(d->tz, s->tz, n * sizeof(float));
ft_memcpy(d->mat_ids, s->mat_ids, n * sizeof(uint16_t));
d->count = n;
}

voidscene_reset(t_gui *gui)
{
t_scene_snap*s;
t_scene*sc;

if (!gui->map_info.current)
return ;
s = gui->map_info.current->snap;
sc = gui->scene;
restore_prim_soa(&sc->primitives, &s->prims);
restore_tri_soa(&sc->tri_soa, &s->tris);
sc->light_count = s->light_count;
ft_memcpy(sc->lights, s->lights, s->light_count * sizeof(t_light));
sc->mat_count = s->mat_count;
ft_memcpy(sc->materials, s->materials, s->mat_count * sizeof(t_material));
sc->ambient = s->ambient;
sc->camera = s->camera;
reset_cam_ctrl(gui);
clear_selection(gui);
rebuild_bvh(gui);
gui->render.dirty = true;
}
