/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fdf.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 06:41:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 02:57:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PRIMITIVES_FDF_H
# define TYPES_PRIMITIVES_FDF_H

# include "t_meshes.h"

typedef enum e_fdf_mode
{
	FDF_MODE_HEIGHT_GRADIENT,
	FDF_MODE_PICTURE,
}					t_fdf_mode;

typedef struct s_fdf
{
	t_mesh				*mesh;
	t_vec2s				dims;
	size_t				row;
}						t_fdf;

typedef struct s_fdf_task
{
	t_mesh				*mesh;
	t_vec2s				dims;
	volatile size_t		next_row;
	volatile size_t		next_idx;
}						t_fdf_task;

#endif
