/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:50:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 19:50:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

/* std */
# include <X11/X.h>
# include <X11/keysym.h>
# include <dirent.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>
# include <zlib.h>

/* package */
# include "libft.h"
# include "mlx.h"

/* 2. MODULE TYPES & ENUMS */
# define DEBUG 0
# define GLB_MAGIC 0x46546C67
# define CHUNK_JSON 0x4E4F534A
# define CHUNK_BIN 0x004E4942
# define BVH_BINS 16

/* 2. CONSTANTS */
# define TILE_SIZE 32
# define ZOOM_SPEED 2.0
# define MOUSE_SENSITIVITY 0.005

# define EPSILON 1e-6
# define MAX_LEAF_OBJECTS 4
# define PARSER_BUF_SIZE 65536

# define INIT_SPHERE_CAP 16
# define INIT_PLANE_CAP 16
# define INIT_MESH_CAP 8
# define INIT_ANIM_CAP 4
# define INIT_GROUP_CAP 32
# define INIT_MAT_CAP 32
# define INIT_LIGHT_CAP 8
# define INIT_CYL_CAP 16
# define INIT_TRI_CAP 64
# define INIT_RECT_CAP 32
# define INIT_PYRAMID_CAP 32
# define INIT_BOX_CAP 32
# define INIT_CAPSULE_CAP 32
# define MAX_VALUE 1e30



#endif