/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:07:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:46:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "maths.h"
# include "mesh.h"

typedef struct s_fdf_grid
{
	float	*z;
	int		w;
	int		h;
}			t_fdf_grid;

struct s_scene;

int		fdf_parse_row(char *line, float **zp, int *count, int *cap);
int		fdf_push_tri(struct s_scene *s, t_vec3 *v, t_vec3 col);
int		fdf_gen_mesh(struct s_scene *s, t_fdf_grid *g, t_mesh_conf *c);
void	fdf_group_objs(struct s_scene *s, int base, const char *path);

#endif
