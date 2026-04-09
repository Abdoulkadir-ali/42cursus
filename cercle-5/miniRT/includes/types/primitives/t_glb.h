/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_glb.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 06:34:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:32:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PRIMITIVES_GLB_H
# define TYPES_PRIMITIVES_GLB_H

# include "t_meshes.h"

typedef struct s_glb_mesh_task
{
	t_json_value	*json;
	char			*bin;
	t_mesh			*meshes;
	t_index			*mat_ids;
	size_t			count;
	size_t			next_idx;
	size_t			fallback_mat_id;
	t_scene			*scene;
}	t_glb_mesh_task;

typedef struct s_extract_attr
{
	unsigned char	*tmp;
	int				comp_type;
	size_t			c_sz;
}	t_extract_attr;

typedef struct s_glb_mat
{
	t_mesh_resource	*out;
	void			*mlx_ptr;
	t_json_value	*json;
	char			*bin;
	size_t			mat_idx;
	t_index			*out_ids;
}	t_glb_mat;

#endif
