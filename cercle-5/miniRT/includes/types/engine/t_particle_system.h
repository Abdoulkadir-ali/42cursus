/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_particle_system.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 09:15:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_ENGINE_PARTICLE_SYSTEM_H
# define TYPES_ENGINE_PARTICLE_SYSTEM_H

# include <stddef.h>
# include <stdbool.h>
# include "t_maths.h"

/*
** ── Limits ──────────────────────────────────────────────────────────────────
** MAX_PARTICLES   : total SoA slots (alive particles always packed at [0,n))
** MAX_EMITTERS    : per-scene emitter count
** MAX_PROXY_SPHERES: how many particles are rendered as real BVH spheres
**                   (the rest still simulate but are invisible in raytracing)
*/
# define MAX_PARTICLES      65536
# define MAX_EMITTERS       32
# define MAX_PROXY_SPHERES  512

/*
** ── Structure of Arrays ─────────────────────────────────────────────────────
** Alive particles are always packed in [0, alive).
** When a particle dies it is swapped with the last alive slot and alive--.
** When a particle spawns it occupies slot [alive] and alive++.
**
** double is used throughout (instead of float) so we don't fight the rest
** of the engine's coordinate system.  AVX/AVX2 can still vectorise doubles
** 4-wide with __m256d.
*/
typedef struct s_particle_soa
{
	double		*px;		/* world position X */
	double		*py;		/* world position Y */
	double		*pz;		/* world position Z */
	double		*vx;		/* velocity X */
	double		*vy;		/* velocity Y */
	double		*vz;		/* velocity Z */
	double		*age;		/* elapsed lifetime (seconds) */
	double		*life;		/* total lifetime (seconds) */
	double		*temp;		/* normalised temperature [0,1] → blackbody */
	double		*size;		/* visual radius for proxy sphere */
	size_t		alive;		/* number of live particles */
	size_t		cap;		/* allocated array length */
}				t_particle_soa;

/*
** ── Emitter shapes ──────────────────────────────────────────────────────────
*/
typedef enum e_emitter_shape
{
	EMITTER_POINT,		/* all particles spawn at pos */
	EMITTER_SPHERE_SURF,	/* spawn on surface of sphere of radius spread */
	EMITTER_CONE		/* spawn in a cone of half-angle spread around dir */
}	t_emitter_shape;

/*
** ── Particle Emitter ────────────────────────────────────────────────────────
** Scene-file keyword:  pe <x,y,z> <dx,dy,dz> <rate> <speed>
**                         <life_min> <life_max> <size>
**                         [spread] [temp_min] [temp_max]
**
**   rate     : particles / second
**   speed    : launch speed along dir (m/s)
**   size     : visual radius of each proxy sphere (scene units)
**   spread   : cone half-angle (radians) for EMITTER_CONE,
**              or sphere radius for EMITTER_SPHERE_SURF
**   temp     : normalised temperature at birth [0,1].  Drives blackbody colour
**              and proxy sphere emission.
**   _accum   : internal fractional spawn counter (not parsed)
*/
typedef struct s_emitter
{
	t_vec3			pos;
	t_vec3			dir;
	double			rate;
	double			speed;
	double			life_min;
	double			life_max;
	double			size;
	double			temp_min;
	double			temp_max;
	double			spread;
	t_emitter_shape	shape;
	bool			active;
	double			_accum;
}	t_emitter;

# define BB_STOP_COUNT 5

typedef struct s_blackbody_stop
{
	double	stop;
	t_vec3	color;
}	t_blackbody_stop;

#endif
