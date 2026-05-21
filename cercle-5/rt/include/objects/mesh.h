/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:24:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:46:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include "maths.h"
# include "shapes.h"

typedef struct s_mesh_conf
{
	t_vec3	origin;
	t_vec3	rot;
	float	scale;
	float	zscale;
	t_vec3	color;
	t_vec3	emit;
}			t_mesh_conf;

struct s_scene;

int		mesh_load_fdf(struct s_scene *s, const char *path, t_mesh_conf *conf);
int		mesh_load_glb(struct s_scene *s, const char *path, t_mesh_conf *conf);
void	glb_animate(struct s_scene *s, float time);
char	*read_file_all(const char *path);

#endif
