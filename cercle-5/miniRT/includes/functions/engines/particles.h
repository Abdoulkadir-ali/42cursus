/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 10:55:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINES_PARTICLES_H
# define ENGINES_PARTICLES_H

# include "scene.h"
# include "t_physics.h"
# include "t_particle_system.h"
# define PART_GRAV_SOFT2     0.25
# define PART_GRAV_ACCEL_CAP 200.0

/* ── SoA lifecycle ──────────────────────────────────────────────────────── */
t_particle_soa	*particle_soa_alloc(size_t n);
void			particle_soa_free(t_particle_soa *soa);

/* ── Scene-level API ────────────────────────────────────────────────────── */
bool			scene_add_emitter(t_scene *scene, t_emitter em);

/* ── Emission ───────────────────────────────────────────────────────────── */
void			emit_particles(t_particle_soa *soa, t_emitter *em, double dt);

/* ── Physics forces ─────────────────────────────────────────────────────── */
void			particle_apply_attractors(t_particle_soa *soa, t_scene *scene,
					double big_g);
void			particle_apply_rigid_bodies(t_particle_soa *soa, t_scene *scene,
					double big_g);

/* ── Per-frame step ─────────────────────────────────────────────────────── */

/*
** particle_systems_step()
**   • Lazy-initialises MAX_PROXY_SPHERES proxy-sphere slots in scene->spheres
**     and their dedicated materials on first call.
**   • Fires each emitter (rate-based spawn with dt accumulator).
**   • SoA integration: pos += vel*dt, vel += gravity*dt.
**   • Applies attractor and rigid-body gravitational forces.
**   • Ages particles; kills those past their lifetime (swap-with-last).
**   • Writes live particle state into the pre-allocated proxy spheres so
**     the BVH rebuild (called by update_physics after this) sees them.
*/
void			particle_systems_step(t_scene *scene, double dt,
					const t_physics_settings *s);

/* ── Step internal helpers (to be split) ────────────────────────────────── */
t_vec3			blackbody_color(double t);
void			init_proxy_spheres(t_scene *scene);
void			update_proxy_spheres(t_scene *scene);
/* ── Utilities ──────────────────────────────────────────────────────────── */
double			rnd01(unsigned int *seed);
double			rnd_range(double lo, double hi, unsigned int *seed);
void			age_and_kill(t_particle_soa *soa, double dt);

#endif
