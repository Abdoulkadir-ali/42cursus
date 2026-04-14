/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_soft_body.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:27:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_ENGINE_SOFT_BODY_H
# define TYPES_ENGINE_SOFT_BODY_H

# include <stddef.h>
# include <stdbool.h>

# define MAX_SB_PARTICLES 2048
# define MAX_SB_SPRINGS   16384
# define SB_PARTICLE_MASS 0.5

/*
** One mass point in a soft body simulation.
** inv_mass == 0.0 means the particle is pinned (immovable).
*/
typedef struct s_sb_particle
{
	t_vec3	pos;
	t_vec3	vel;
	t_vec3	force;
	double	inv_mass;
}			t_sb_particle;

/*
** A Hooke spring connecting two particles by index.
** Includes a velocity-projection damping term.
*/
typedef struct s_sb_spring
{
	size_t	a;
	size_t	b;
	double	rest_len;
	double	stiffness;
	double	damping;
}			t_sb_spring;

/*
** Soft body: mass-spring lattice derived from a mesh.
** After each step the deformed positions are written back into
** scene->meshes[mesh_idx].geometry.vertices and normals are recomputed.
*/
typedef struct s_sb_params
{
	size_t	mesh_idx;
	double	stiffness;
	double	damping;
	t_vec3	offset;
}			t_sb_params;

typedef struct s_soft_body
{
	t_sb_particle	*particles;
	size_t			particle_count;
	t_sb_spring		*springs;
	size_t			spring_count;
	size_t			mesh_idx;
	double			stiffness;
	double			damping;
	bool			active;
}					t_soft_body;

#endif
