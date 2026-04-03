/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:09:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PARSING_PARSER_H
# define TYPES_PARSING_PARSER_H

# define PARSER_BUF_SIZE 65536
# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_parser
{
	int					fd;
	char				buffer[PARSER_BUF_SIZE + 1];
	size_t				cursor;
	size_t				bytes_read;
	bool				eof;
}						t_parser;

typedef struct s_parse_obj
{
	t_type				type;
	union
	{
		t_sphere		sphere;
		t_plane			plane;
		t_cylinder		cylinder;
		t_cone			cone;
		t_tri_shape		tri_shape;
		t_rect			rect;
		t_pyramid		pyramid;
		t_box			box;
		t_capsule		capsule;
		t_light			light;
		t_camera		camera;
		t_ambient		ambient;
		t_mesh_info		mesh_info;
	}					data;
}						t_parse_obj;

typedef struct s_rt
{
	t_parser			*parser;
	int					fd;
	char				id[16];
	t_parse_obj			obj;
	bool				status;
}						t_rt;

#endif
