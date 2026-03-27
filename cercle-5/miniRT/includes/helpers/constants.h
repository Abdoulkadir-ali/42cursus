/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:02:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:02:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define MAIN_H
# define STB_WRAPPER_H
# define EDITOR_H
# define COL_SELECTED 0x20D870U
# define COL_PANEL_HDR 0x1A1A28U
# define COL_ROW_HOVER 0x1E2030U
# define COL_ROW_SEL 0x2A3040U
# define COL_SLIDER_BG 0x1A1A20U
# define COL_SLIDER_FG 0xE0A820U
# define INSPECTOR_W 280
# define SCENE_PANEL_W 220
# define ROW_H 24
# define CRUD_PANEL_H 36
# define SLIDER_H 8
# define SLIDER_KNOB_W 3
# define SLIDER_KNOB_H 12
# define SLIDER_PAD 24
# define SLIDER_Y_OFF 13
# define SLIDER_VAL_X 46
# define CRUD_BTN_H 24
# define CRUD_BTN_W 52
# define CRUD_ADD_W 90
# define POPUP_W 360
# define POPUP_ITEM_H 36
# define POPUP_PAD 16
# define POPUP_TITLE_H 36
# define POPUP_FMT_H 36
# define POPUP_INPUT_H 36
# define POPUP_ERR_H 16
# define POPUP_BTN_H 36
# define COL_POPUP_DIM 0x0D0D14U
# define COL_POPUP_BG 0x1A1A28U
# define COL_POPUP_BTN 0x22222EEU
# define COL_POPUP_BTN_OK 0x1A2A1AU
# define COL_POPUP_BTN_CANCEL 0x2A1A1AU
# define COL_POPUP_ERR 0xFF4444U
# define COL_POPUP_ERR_TEXT 0xFF6666U
# define SCENE_PANEL_PAD_X 12
# define SCENE_PANEL_PAD_Y 8
# define SCENE_PANEL_HDR_X 8
# define SCENE_PANEL_EMPTY_COL 0x505060
# define INSPECTOR_HDR_Y 50
# define INSPECTOR_TAB_Y 70
# define INSPECTOR_TAB_H 24
# define INSPECTOR_PAD 8
# define INSPECTOR_TAB_MIN_Y 60
# define INSPECTOR_TAB_MAX_Y 84
# define TR_PANEL_START_Y 104
# define TR_PANEL_STEP_Y 30
# define SL_POS_MIN -100.0
# define SL_POS_MAX 100.0
# define SL_ROT_MIN -3.14159265
# define SL_ROT_MAX 3.14159265
# define SL_SCALE_MIN 0.01
# define SL_SCALE_MAX 10.0
# define SL_MASS_MIN 0.0
# define SL_MASS_MAX 1000.0
# define SL_ELAST_MIN 0.0
# define SL_ELAST_MAX 1.0
# define SL_FRIC_MIN 0.0
# define SL_FRIC_MAX 1.0
# define SL_ROUGH_MIN 0.0
# define SL_ROUGH_MAX 1.0
# define SL_METAL_MIN 0.0
# define SL_METAL_MAX 1.0
# define SL_OPAC_MIN 0.0
# define SL_OPAC_MAX 1.0
# define SL_REFL_MIN 0.0
# define SL_REFL_MAX 1.0
# define SL_IOR_MIN 1.0
# define SL_IOR_MAX 2.4
# define SL_COL_MIN 0.0
# define SL_COL_MAX 1.0
# define SL_EMIT_MIN 0.0
# define SL_EMIT_MAX 50.0
# define SL_INTENSITY_MIN 0.0
# define SL_INTENSITY_MAX 20.0
# define SL_AMB_MIN 0.0
# define SL_AMB_MAX 1.0
# define SL_CUTOFF_MIN 0.0
# define SL_CUTOFF_MAX 180.0
# define GUI_H
# define TILE_SIZE 32
# define ZOOM_SPEED 2.0
# define MOUSE_SENSITIVITY 0.005
# define BUTTON_LEFT 1
# define BUTTON_MIDDLE 2
# define BUTTON_RIGHT 3
# define BUTTON_SCROLL_UP 4
# define BUTTON_SCROLL_DOWN 5
# define RENDER_W 2560
# define RENDER_H 1440
# define GUI_AUTOREFRESH_PHYSICS 1
# define GUI_AUTOREFRESH_SCALE 2
# define PANEL_RADIUS 6
# define COL_BG 0x0A0A12
# define COL_ACCENT 0xE0A820
# define COL_FPS 0x20E060
# define COL_TEXT 0xD0D0D8
# define COL_HOVER 0x20C8D0
# define COL_BORDER 0x333340
# define MAX_INSPECT_TABS 4
# define WINDOW_H
# define OBJECTS_H
# define GLB_MAGIC 0x46546C67
# define CHUNK_JSON 0x4E4F534A
# define CHUNK_BIN 0x004E4942
# define BVH_BINS 16
# define CACHE_CAP 64
# define SURFACE_H
# define BITS_PER_BYTE 8
# define TEX_DEFAULT_SCALE 1.0
# define TEX_DEFAULT_BPP 32
# define TEX_CH_RGBA 4
# define TEX_CENTER_OFFSET 0.5
# define SCENE_H
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
# define SCALE_EPSILON 1e-6
# define HALF_SCALE 0.5f
# define PRIMITIVES_H
# define PHYSICS_H
# define MAX_SUB_SHAPES 32
# define EPA_MAX_VERTS 32
# define EPA_MAX_FACES 64
# define MAX_BODY_PAIRS 512
# define EPA_MAX_ITER 30
# define EPA_TOL 1e-5
# define GLOBAL_DAMPING 0.12
# define DBVT_MAX_NODES 512
# define DBVT_MAX_LEAVES 256
# define MAX_CONTACTS 1024
# define SOLVER_ITERATIONS 8
# define BAUMGARTE 0.2
# define SLOP 0.01
# define RESTITUTION_SLOP 0.2
# define PHYS_NUM_TYPES 7
# define DBVT_FAT_MARGIN 0.1
# define DBVT_NULL -1
# define ANIMATIONS_H
# define RAYTRACING_H
# define MAX_DEPTH 5
# define COLOR_MAX 255.0
# define COLOR_MIN 0.0
# define SHININESS_SCALE 200.0
# define SHININESS_OFFSET 2.0
# define METALLIC_REDUCT 0.5
# define METALLIC_BOOST 0.9
# define REFRACT_MAX_DEG 180.0
# define REFRACT_IOR_SCALE 2.0
# define MAG_EPSILON 1e-6
# define SHADOW_BIAS 1e-4
# define WEIGHT_MIN 0.02
# define SAFE_RCP_MIN 1e-20
# define TRACE_MAX_DIST 1e30
# define ATTENUATION_K 0.05
# define MAX_EMISSIVE_DIST_SQ 2500.0
# define EMISSIVE_SURF_OFF 0.01
# define EMISSIVE_BR_SCALE 3.0
# define EPSILON_MUL 10.0
# define EPSILON 1e-6
# define NDOTL_MIN 0.02
# define NDOTH_MIN 0.01
# define ENGINE_H
# define PROFILER_H
# define PROF_ID_g_mesh_calls PROF_MESH_CALLS
# define PROF_ID_g_mesh_aabb_tests PROF_MESH_AABB_TESTS
# define PROF_ID_g_mesh_tri_tests PROF_MESH_TRI_TESTS
# define PROF_ID_g_mesh_occ_calls PROF_MESH_OCC_CALLS
# define DEBUG_H
# define DEBUG 1
# define MATHS_H
# define UTILS_H
# define HELPER_H
# define PARSER_H
# define MAX_LEAF_OBJECTS 4
# define PARSER_BUF_SIZE 65536

#endif /* CONSTANTS_H */
