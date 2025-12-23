/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:43:55 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 22:14:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/* ========== GEOMETRY CONSTANTS ========== */
# ifndef BAD_VALUE
#  define BAD_VALUE -2000000000.0
# endif

/* ========== WINDOW CONSTANTS ========== */
# define WINDOW_WIDTH_RATIO 0.85
# define WINDOW_HEIGHT_RATIO 0.85
# define MIN_WINDOW_WIDTH 1024
# define MIN_WINDOW_HEIGHT 768
# define MAX_WINDOW_WIDTH 1920
# define MAX_WINDOW_HEIGHT 1080

/* ========== OPTIMIZATION DEFAULTS ========== */
# define DEFAULT_BG_COLOR 0x000000
# define DEFAULT_Z_SCALE 1.0
# define DEFAULT_FRUSTUM_MARGIN 50
# define DEFAULT_DAMPENING_THRESHOLD 0
# define MIN_LOD_LEVEL 1
# define MAX_LOD_LEVEL 10
# define MIN_Z_SCALE 0.1
# define MAX_Z_SCALE 5.0
# define MIN_FRUSTUM_MARGIN 0
# define MAX_FRUSTUM_MARGIN 500
# define MIN_DAMPENING_THRESHOLD -100
# define MAX_DAMPENING_THRESHOLD 100
# define KEY_MAP_SIZE 0x10000

/* ========== GRAPHICS CONSTANTS ========== */
# define NUM_THREADS 8
# define DEFAULT_LOD_LEVEL 1.0
# define FP_SHIFT 16
# define FP_16 65536.0
# define DRAW_LIMIT -1000000.0
# define DEFAULT_TARGET_POINTS 1000000UL
# define MAX_DETAIL_LEVEL 7
# define MIN_DETAIL_LEVEL -5

# define B_USE_Z 1
# define B_COLOR_SHIFT 2

/* ========== GUI CONSTANTS ========== */
# define GUI_PANEL_WIDTH 280
# define GUI_PADDING 15
# define GUI_LINE_HEIGHT 18
# define GUI_TITLE_HEIGHT 25

# define GUI_BG_COLOR 0x1A1A1A
# define GUI_BORDER_COLOR 0x404040
# define GUI_TEXT_COLOR 0xE0E0E0
# define GUI_TITLE_COLOR 0x00D4FF
# define GUI_VALUE_COLOR 0x00FF88
# define GUI_KEY_COLOR 0xFFAA00

/* ========== CAMERA CONSTANTS ========== */
# define DEFAULT_ZOOM_AVAILABLE_WIDTH 0.8
# define DEFAULT_ZOOM_AVAILABLE_HEIGHT 0.8
# define DEFAULT_ZOOM_PADDING 1.0
# define DEFAULT_ZOOM_MIN 0.1
# define DEFAULT_ZOOM_MAX 10.0
# define DEFAULT_Y_ADJUST_FACTOR 0.5
# define DEFAULT_CAMERA_ROTATION_X 0.0
# define DEFAULT_CAMERA_ROTATION_Y 0.0
# define DEFAULT_CAMERA_ROTATION_Z 0.0
# define DEFAULT_ROTATION_SPEED 0.05

#endif
