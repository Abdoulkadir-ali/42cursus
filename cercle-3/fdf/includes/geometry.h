/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 17:43:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

/* ========== IMPORTS ========== */
# include "define.h"
# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <xmmintrin.h>

/* ========== VECTORS ========== */

typedef struct s_vec2
{
	int					x;
	int					y;
}						t_vec2;

typedef struct s_vec2d
{
	double				x;
	double				y;
}						t_vec2d;

typedef struct s_vec3
{
	int					x;
	int					y;
	int					z;
}						t_vec3;

typedef struct s_vec3d
{
	double				x;
	double				y;
	double				z;
}						t_vec3d;

typedef struct s_vecu2
{
	unsigned int		x;
	unsigned int		y;
}						t_vecu2;

typedef struct s_vecu3
{
	unsigned int		x;
	unsigned int		y;
	unsigned int		z;
}						t_vecu3;

typedef struct s_point
{
	t_vec3d				pos;
	unsigned int		color;
}						t_point;

typedef struct s_matrix4
{
	float				m[4][4];
}						t_matrix4;

/* Vector Constructors */
t_vec2					create_vec2(int x, int y);
t_vec2d					create_vec2d(double x, double y);
t_vec3					create_vec3(int x, int y, int z);
t_vec3d					create_vec3d(double x, double y, double z);

/* Vector Operations */
void					vec2_add(t_vec2 *self, t_vec2 other);
void					vec2_sub(t_vec2 *self, t_vec2 other);
void					vec2_multiply(t_vec2 *self, t_vec2 other);
void					vec2_divide(t_vec2 *self, t_vec2 other);
void					vec2_multiply_scalar(t_vec2 *self, int scalar);
int						vec2_len(t_vec2 v);
int						vec2_min(t_vec2 v);
int						vec2_max(t_vec2 v);

void					vec2d_add(t_vec2d *self, t_vec2d other);
void					vec2d_sub(t_vec2d *self, t_vec2d other);
void					vec2d_multiply(t_vec2d *self, t_vec2d other);
void					vec2d_divide(t_vec2d *self, t_vec2d other);
void					vec2d_multiply_scalar(t_vec2d *self, double scalar);
double					vec2d_len(t_vec2d v);

void					vec3_add(t_vec3 *self, t_vec3 other);
void					vec3_sub(t_vec3 *self, t_vec3 other);
void					vec3_multiply(t_vec3 *self, t_vec3 other);
void					vec3_divide(t_vec3 *self, t_vec3 other);
void					vec3_multiply_scalar(t_vec3 *self, int scalar);
double					vec3_len(t_vec3 v);

void					vec3d_add(t_vec3d *self, t_vec3d other);
void					vec3d_sub(t_vec3d *self, t_vec3d other);
void					vec3d_multiply(t_vec3d *self, t_vec3d other);
void					vec3d_divide(t_vec3d *self, t_vec3d other);
void					vec3d_multiply_scalar(t_vec3d *self, double scalar);
double					vec3d_len(t_vec3d v);

/* Unsigned Vectors */
t_vecu2					create_vecu2(unsigned int x, unsigned int y);
t_vecu3					create_vecu3(unsigned int x, unsigned int y,
							unsigned int z);

void					vecu2_add(t_vecu2 *self, t_vecu2 other);
void					vecu2_sub(t_vecu2 *self, t_vecu2 other);
void					vecu2_multiply(t_vecu2 *self, t_vecu2 other);
void					vecu2_divide(t_vecu2 *self, t_vecu2 other);
void					vecu2_multiply_scalar(t_vecu2 *self,
							unsigned int scalar);

void					vecu3_add(t_vecu3 *self, t_vecu3 other);
void					vecu3_sub(t_vecu3 *self, t_vecu3 other);
void					vecu3_multiply(t_vecu3 *self, t_vecu3 other);
void					vecu3_divide(t_vecu3 *self, t_vecu3 other);
void					vecu3_multiply_scalar(t_vecu3 *self,
							unsigned int scalar);

/* Distance / Utils */
unsigned int			vecu2_len(t_vecu2 v);
unsigned int			vecu2_min(t_vecu2 v);
unsigned int			vecu2_max(t_vecu2 v);

double					vecu3_len(t_vecu3 v);

/* ========== MODULES ========== */
# include "color.h"

/* ========== MAPS / MESHES ========== */

typedef enum e_map_style
{
	MAP_STYLE_DEFAULT,
	MAP_STYLE_GRADIENT,
	MAP_STYLE_SOLID,
	MAP_STYLE_ZEBRA,
	MAP_STYLE_NEON,
	MAP_STYLE_COUNT
}						t_map_style;

typedef struct s_map_style_config
{
	int					line_thickness;
	int					point_thickness;
	unsigned int		line_color;
	unsigned int		point_color;
	int					style;
}						t_map_style_config;

typedef struct s_map_points
{
	t_vec3d				*pos;
	t_vec3d				*raw;
	unsigned int		*color;
}						t_map_points;

typedef struct s_map
{
	size_t				width;
	size_t				height;
	t_vec2				min_max_z;
	int					min_proj_z;
	int					max_proj_z;
	double				z_divisor;
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
}						t_maps;

/* Map Management */
t_maps					init_maps(void);
void					init_map_list(t_maps *m);
void					load_map_files(t_maps *m, DIR *dir, size_t count);
t_map					*select_initial_map(t_maps *manager);
t_map					*init_map(char *filename);
t_map					*create_test_grid(void);
t_map					*load_map(char *filename);
t_map					*tesselate_mesh(t_map *src);
t_map					*generate_tesselated_map(t_map *base, int level);
t_map					*extract_submap(t_map *src, t_vec2 min, t_vec2 max);
t_map					*generate_tesselated_submap(t_map *base, t_vec2 min,
							t_vec2 max, int level);
void					free_map(t_map *map);

/* Map Data Processing */
void					find_min_max_z(t_map *map, float *min, float *max);
void					calculate_min_max_z(t_map *map);
void					calculate_z_divisor(t_map *map);
void					apply_map_style(t_map *map);
void					cycle_map_style(t_maps *m);
void					cycle_map(t_maps *m);

/* Parsing Helper Utils (Internal? Exposing for now) */
unsigned int			get_solid_color(int z);
unsigned int			get_zebra_color(int z);
unsigned int			get_neon_color(int z);
unsigned int			get_map_line_color(t_vec3 v, t_map_style style);
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
	double				z_divisor;
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

/* Matrix Operations */
t_matrix4				matrix_identity(void);
t_matrix4				matrix_multiply(t_matrix4 a, t_matrix4 b);
t_matrix4				matrix_translation(float x, float y, float z);
t_matrix4				matrix_scale(float x, float y, float z);

#endif
