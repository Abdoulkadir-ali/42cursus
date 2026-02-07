/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 18:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "objects/objects.h"

typedef struct s_heightmap
{
	double		**map;
	int			width;
	int			height;
	t_vec3		rgb;
}				t_heightmap;

# include "libft.h"

/* .fdf specific parsing prototypes */
bool	parse_fdf(const char *path, t_scene *scene);

#endif
