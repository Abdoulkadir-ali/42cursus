/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 04:40:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

/* ========== IMPORTS ========== */
# include <dirent.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <time.h>

/* ========== IMPORTS ========== */
# include "define.h"
# include "libft.h"
# include "primitives.h"

/* ========= THREADS ========== */
typedef struct s_load_ctx
{
	struct dirent	*entry;
	char		path[256];
	size_t		i;
	t_thread_res	res;
} t_load_ctx;

typedef struct s_thread_res
{
	pthread_t			*threads;
	int					*active;
	size_t				count;
}						t_thread_res;

typedef struct s_load_thread_data
{
	t_maps				*m;
	char				*path;
	size_t				index;
}						t_load_thread_data;

/* ========== VECTORS ========== */
typedef struct s_tess_diagonal_ctx
{
	int					idx;
	t_vec3d				p1;
	t_vec3d				p2;
	t_vec3d				p3;
	t_vec3d				p4;
	t_vec3d				res1;
	t_vec3d				res2;
	t_vec3				colors1;
	t_vec3				colors2;
	t_vec3				col_vec;
	t_vec3				col_vec1;
	t_vec3				col_vec2;
	t_vec3				sc1;
	t_vec3				sc2;
	t_vec3				sc3;
	t_vec3				sc4;
	t_vec3				scol_vec1;
	t_vec3				scol_vec2;
	t_vec3				final_source;
}						t_tess_diagonal_ctx;

typedef struct s_tess_horizontal_ctx
{
	int					idx;
	t_vec3d				p1;
	t_vec3d				p2;
	t_vec3				c1;
	t_vec3				c2;
	t_vec3				sc1;
	t_vec3				sc2;
}						t_tess_horizontal_ctx;

typedef struct s_tess_vertical_ctx
{
	int					idx;
	t_vec3d				p1;
	t_vec3d				p2;
	t_vec3				col1;
	t_vec3				col2;
	t_vec3				sc1;
	t_vec3				sc2;
}						t_tess_vertical_ctx;

typedef struct s_tess_direct_ctx
{
	int					idx;
}						t_tess_direct_ctx;

typedef struct s_tess_compute_ctx
{
	t_vec2				dst_pos;
	t_vec2				src_pos;
}						t_tess_compute_ctx;

typedef struct s_set_point_ctx
{
	t_vec2				dst_pos;
	t_vec3d				pos;
	t_vec3				color;
	t_vec3				source_color;
}						t_set_point_ctx;

/* ========== MAPS / MESHES ========== */

typedef enum e_map_style
{
	MAP_STYLE_DEFAULT,
	MAP_STYLE_GRADIENT,
	MAP_STYLE_SOLID,
	MAP_STYLE_ZEBRA,
	MAP_STYLE_NEON,
	MAP_STYLE_RAW,
	MAP_STYLE_COUNT
}						t_map_style;

typedef struct s_map_style_config
{
	int					line_thickness;
	int					point_thickness;
	t_vec3				line_color;
	t_vec3				point_color;
	int					style;
}						t_map_style_config;

typedef struct s_map_points
{
	t_vec3d				*pos;
	t_vec3d				*raw;
	t_vec3				*color;
	t_vec3				*source_color;
}						t_map_points;

typedef struct s_map
{
	size_t				width;
	size_t				height;
	t_vec2				min_max_z;
	int					min_proj_z;
	int					max_proj_z;
	unsigned int		z_divisor;
	t_map_points		points;
	t_map_style_config	style;
}						t_map;

typedef struct s_maps
{
	t_map				**maps;
	char				**map_files;
	size_t				count;
	int					current_index;
	t_map				*current_map;
	int					generated_id;
	int					is_generating;
}						t_maps;

typedef struct s_height_color_ctx
{
	double				ratio;
	double				shift;
	double				effective_z;
	double				max_effective;
}						t_height_color_ctx;

typedef struct s_rgb
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_rgb;

int						clamp(int value, int min, int max);
double					clamp_d(double value, double min, double max);

t_vec3					int_color_to_rgb(unsigned int color);
unsigned int			rgb_to_int(t_vec3 color);

t_vec3					create_color(int r, int g, int b);
unsigned int			create_color_rgb(t_vec3 rgb);
t_vec3					shift_color(t_vec3 color, t_vec3 shift);
t_vec3					create_color_wrap(int r, int g, int b);

t_vec3					interpolate_color(t_vec3 color1, t_vec3 color2,
							double ratio);
t_vec3					get_height_color(double z, int min_z, int max_z);

void					init_map_list(t_maps *m, char *dir_path);
size_t					count_fdf_files(DIR *dir);
void					load_map_files(t_maps *m, DIR *dir, size_t count,
							char *dir_path);
int						is_directory(const char *path);

t_map					*create_test_grid(void);
t_map					*load_map(char *filename);
t_map					*tesselate_mesh(t_map *src);
t_map					*init_tesselated_map(t_map *src, size_t *new_w,
							size_t *new_h);
int						allocate_tesselated_points(t_map *dst);
void					fill_tesselated_points(t_map *dst, t_map *src);
void					finalize_tesselated_map(t_map *dst, t_map *src);
void					compute_tesselated_point(t_map *src, t_map *dst,
							t_vec2 pos);
t_vec3d					mix_pos(t_vec3d p1, t_vec3d p2, double ratio);
t_map					*extract_submap(t_map *src, t_vec2 min, t_vec2 max);
t_map					*generate_tesselated_map(t_map *base, int level);
t_map					*generate_tesselated_submap(t_map *base, t_vec2 min,
							t_vec2 max, int level);
void					free_map(t_map *map);

/* Map Data Processing */
void					find_min_max_z(t_map *map, float *min, float *max);
void					calculate_min_max_z(t_map *map);
void					calculate_z_divisor(t_map *map);
void					apply_map_style(t_map *map);

void					cycle_map(t_maps *m);
t_map					*generate_and_replace_map(t_maps *maps);

t_vec3d					mix_pos(t_vec3d p1, t_vec3d p2, double ratio);
void					set_point(t_map *dst, t_set_point_ctx ctx);
void					handle_direct_copy(t_map *src, t_map *dst,
							t_vec2 dst_pos, t_vec2 src_pos);
void					handle_horizontal_interp(t_map *src, t_map *dst,
							t_vec2 dst_pos, t_vec2 src_pos);
void					handle_vertical_interp(t_map *src, t_map *dst,
							t_vec2 dst_pos, t_vec2 src_pos);
void					handle_diagonal_interp(t_map *src, t_map *dst,
							t_vec2 dst_pos, t_vec2 src_pos);
void					init_diagonal_ctx(t_tess_diagonal_ctx *ctx, t_map *src);

/* Parsing Helper Utils (Internal? Exposing for now) */
t_vec3					get_solid_color(int z);
t_vec3					get_zebra_color(int z);
t_vec3					get_neon_color(int z);
t_vec3					get_map_line_color(t_vec3 v, t_map_style style);
int						allocate_map_points(t_map *map);
void					parse_map_data(t_map *map, int fd);
void					get_map_dimensions(int fd, size_t *width,
							size_t *height);

/* Map Construction Helpers */
t_map					*allocate_map_arrays(t_map *map);
void					init_grid_points(t_map *map);

/* Parser Helpers */
int						is_empty_line(char *line);
int						count_words(char *line);
void					parse_line(char *line, t_map *map, int y);

/* Helper structs for map building (Internal) */
typedef struct s_min_max_ctx
{
	int					first;
	double				z;
	t_vec2				pos;
	size_t				idx;
}						t_min_max_ctx;

typedef struct s_process_proj_row_ctx
{
	t_min_max_ctx		*min_max_ctx;
	t_map				*map;
	unsigned int		z_divisor;
	int					y;
}						t_process_proj_row_ctx;

typedef struct s_find_min_max_ctx
{
	t_vec2				pos;
	size_t				idx;
	float				val;
	int					first;
	float				min_val;
	float				max_val;
}						t_find_min_max_ctx;

#endif
