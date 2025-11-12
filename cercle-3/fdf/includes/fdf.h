/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:31 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:55:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_map t_map;
typedef struct s_camera t_camera;
typedef struct s_mouse t_mouse;
typedef struct s_keys t_keys;
typedef struct s_point t_point;
typedef struct s_map_render_config t_map_render_config;

/* ========== SYSTEM INCLUDES ========== */
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

/* ========== PROJECT HEADERS ========== */
# include "libft.h"
# include "vectors.h"
# include "camera.h"
# include "color.h"
# include "controls.h"
# include "core.h"
# include "events.h"
# include "graphics.h"
# include "gui.h"
# include "map.h"
# include "projection.h"

void	init_window_size(t_data *data);
void	init_mouse(t_data *data);
void	init_keys(t_data *data);
void	init_map_config(t_data *data);
void	init_camera(t_data *data);
void	adjust_camera_to_map(t_data *data);

#endif
