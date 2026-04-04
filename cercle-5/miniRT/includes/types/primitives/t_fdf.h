/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fdf.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 06:41:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 06:41:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PRIMITIVES_FDF_H
# define TYPES_PRIMITIVES_FDF_H

# include "t_meshes.h"

typedef struct s_fdf_task
{
	t_mesh	*mesh;
	int		w;
	int		h;
	size_t	next_row;
}	t_fdf_task;

#endif
