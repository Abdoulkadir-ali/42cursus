/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 03:01:01 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:26:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEX_DOOR 4
# define TEX_DOOR_OPEN 5
# define TEX_FLOOR 6
# define TEX_CEIL 7
# define TEX_SPRITE 8
# define TEX_COUNT 9

# include "debug.h"
# include "error.h"
# include "exit.h"
# include "libft.h"
# include "maths.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_parser	t_parser;

typedef struct s_wall
{
	t_vec2i				pos;
	t_vec2i				size;
}						t_wall;

typedef struct s_texture
{
	char				*path;
	t_vec2s				size;
	unsigned int		*data;
	bool				stretch;
}						t_texture;

typedef struct s_player_spawn
{
	t_vec2				pos;
	char				dir;
}						t_player_spawn;

typedef struct s_map
{
	char				**grid;
	size_t				width;
	size_t				height;
	t_vec2s				size;
	char				*tex_paths[TEX_COUNT];
	t_texture			textures[TEX_COUNT];
	t_vec3				floor_color;
	t_vec3				ceil_color;
	t_wall				**walls;
	t_player_spawn		player_spawn;
	int					*door_grid_view;
	int					*portal_pair;
	int					*push_grid_view;
	void				*push_walls_view;
	unsigned char		*door_axis;
	void				*active_doors_view;
}						t_map;

typedef struct s_map_manager
{
	t_map				*current_map;
}						t_map_manager;

int						parse_map(const char *filename, t_map *map);
int						validate_map(t_map *map);
void					free_map(t_map *map);
int						is_config_line(const char *line);
int						is_map_line(const char *line);
int						build_grid(t_map *map, char **raw, size_t count);
int						parse_config_line(const char *line, t_map *map);
void					free_raw(char **raw, size_t count);
int						process_line(t_parser *parser, t_map *map, char ***raw,
							t_vec3s *c);
int						validate_xpm_file(const char *path);
void					compute_door_axes(t_map *map);
int						parse_rgb_safe(const char *str, t_vec3 *out);
int						parse_texture_path(t_map *map, int type,
							const char *line);
int						parse_resolution_line(const char *line);
int						parse_floor_line(t_map *map, const char *line);
int						parse_ceil_line(t_map *map, const char *line);
int						parse_wall_line(t_map *map, const char *line);
int						parse_sprite_line(t_map *map, const char *line);

#endif
