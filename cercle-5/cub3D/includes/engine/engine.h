/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 02:53:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 04:29:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

/* UTILITIES */
# include "debug.h"
# include "error.h"
# include "exit.h"
# include "libft.h"
# include "maths.h"
/* DEPENDENCIES */
# include "gameplay.h"
# include "texture.h"
# include "window.h"

/* THIRD-PARTY */
# include <fcntl.h>
# include <unistd.h>

# define INF 1000000000000000000000000000000.0f

typedef struct s_dda
{
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	float				side_dist_x;
	float				side_dist_y;
	float				delta_dist_x;
	float				delta_dist_y;
	float				perp_dist;
	int					side;
	int					tex_idx;
	char				hit_tile;
	t_vec3				origin;
	t_vec2				ray;
	t_vec3				hit_pos;
}						t_dda;

typedef struct s_player_snapshot
{
	t_vec3				render_pos;
	t_vec3				render_dir;
	float				render_pitch_offset;
	float				render_pos_z;
}						t_player_snapshot;

typedef struct s_render_col
{
	t_window			*win;
	t_world				*world;
	int					screen_x;
	t_dda				*dda;
	t_vec2				ray;
	bool				skip_trans;
}						t_render_col;

typedef struct s_floor_data
{
	t_window			*win;
	t_world				*world;
	float				dist;
	int					y;
	t_player_snapshot	player;
}						t_floor_data;

typedef struct s_spr_draw
{
	t_vec2i				start;
	t_vec2i				spr_sz;
	int					dsy;
	float				depth;
	t_map				*map;
}						t_spr_draw;

typedef struct s_render_strip
{
	t_window			*win;
	t_world				*world;
	int					start_x;
	int					end_x;
	float				plane_len;
	t_vec3				dir;
	t_vec2				plane;
}						t_render_strip;

typedef struct s_spr_draw_params
{
	t_window			*win;
	t_world				*world;
	t_entity			*ent;
	t_vec2				transform;
	int					sx;
}						t_spr_draw_params;

typedef struct s_draw_line_data
{
	t_player_snapshot	player_ref;
	float				p_len;
	float				horizon;
	float				p;
	float				eye_h;
	float				dist;
	bool				is_floor;
	t_vec2				plane;
	t_vec2				ray_l;
	t_vec2				ray_r;
	t_vec2				floor_pos;
	t_vec2				floor_step;
	t_texture			*tex;
	t_vec2i				tx;
	uint32_t			*line;
}						t_draw_line_data;

bool					check_door_pixel(t_world *world, int door_idx, t_dda *d,
							t_vec2 ray);
bool					is_wall(t_world *world, t_vec3 pos);
int						load_texture(t_texture *tex, char *path,
							t_world *world, t_app *app);
t_vec3					get_tex_color(t_texture *tex, t_vec2i pos);
void					put_pixel(t_window *window, t_vec2 pos, t_vec3 color);
void					draw_vertical_line(t_window *window, int x,
							t_vec2 y_range, t_vec3 color);
void					draw_square(t_window *window, t_vec2 pos, float size,
							t_vec3 color);
void					draw_minimap_grid(t_window *win, t_world *world,
							t_vec2i start, int view_size);
void					draw_player_arrow(t_window *win, t_world *world,
							int start_x, int start_y);
void					render_raycast_scene(t_window *window, t_world *world);
void					draw_line_pixel(t_floor_data *d, int x, t_vec2 floor,
							t_texture *tex);
void					calc_line_params(t_floor_data *d, float plane_len,
							t_vec2 params[3]);
void					draw_planes(t_window *win, t_world *world,
							float plane_len);
void					draw_column(t_render_col *rc, float plane_len,
							bool skip_trans);
void					draw_column_gap(t_render_col *rc, float plane_len,
							float open);
void					*draw_strip(void *arg);
void					render_minimap(t_window *window, t_world *world);
void					render_entities(t_window *win, t_world *world);
void					sort_entities(t_world *world, size_t *indices,
							float *distances);
void					draw_sprite(t_window *win, t_entity *ent, t_vec2 t,
							t_spr_draw *sd);
void					init_dda(t_dda *d, t_vec3 pos, t_vec2 ray);
void					run_dda(t_dda *d, t_map *map);
t_texture				*get_render_texture(t_render_col *rc);
float					get_wall_x(t_render_col *rc);
void					calc_sprite_pos(t_window *win, t_world *world,
							t_entity *ent, t_vec2 *transform);
void					draw_debug_pixel(t_window *win, t_vec2i pi, float dist,
							t_vec3 color);
void					render_hud(t_window *win, t_world *world);
void					clear_z_buffer(t_window *win);
void					init_render_strip(t_render_strip *s, t_window *win,
							t_world *world);
t_spr_draw				make_spr_draw(t_spr_draw_params params);
void					draw_plane_line(t_window *win, t_world *world, int y,
							t_draw_line_data *d);
void					prepare_line_data(t_draw_line_data *d, t_window *win,
							t_player_snapshot *p, int y);
t_vec3					v3_col(int hex);

t_vec2	project_to_screen(t_window *win, t_world *world, t_vec3 p);
void	draw_debug_sphere(t_window *win, t_world *world, t_debug_shape *shape);

#endif