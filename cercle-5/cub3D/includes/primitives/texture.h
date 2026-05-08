/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 01:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "debug.h"
# include "map.h"
# include "parser.h"
# include <stdbool.h>

# define COL_ALPHA 0xFF000000
# define XPM_HASH_MULT 2654435761u

typedef struct s_world	t_world;
typedef struct s_app	t_app;

typedef struct s_xpm_color
{
	char				*token;
	unsigned int		color;
	unsigned int		key;
	int					is_keep;
}						t_xpm_color;

typedef struct s_xpm_lookup
{
	unsigned int		key;
	unsigned int		idx;
}						t_xpm_lookup;

typedef struct s_xpm_ctx
{
	t_parser			*parser;
	t_texture			*tex;
	t_xpm_color			*colors;
	size_t				ncolors;
	size_t				cpp;
	t_xpm_lookup		*table;
	size_t				table_size;
}						t_xpm;

int						load_texture(t_texture *tex, char *path,
							t_world *world, t_app *app);
int						load_xpm_manual(t_texture *tex, const char *path,
							t_world *world);
int						load_dxpm_manual(t_texture *tex, const char *path,
							unsigned int *prev, t_world *world);
t_vec3					get_tex_color(t_texture *tex, t_vec2i pos);

/* Shared XPM/DXPM internal helpers */
unsigned int			xpm_token_key(const char *s, size_t cpp);
unsigned int			xpm_parse_color(const char *line, size_t cpp);
int						parse_xpm_header(t_xpm *ctx, char *line);
t_xpm_color				*parse_xpm_palette(t_xpm *ctx);
void					free_tab(char **tab);
int						xpm_init_table(t_xpm *xpm);
int						xpm_read_header(t_xpm *xpm);

#endif
