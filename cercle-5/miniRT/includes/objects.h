/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 05:23:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:32:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "maths.h"
# include <fcntl.h>

typedef struct s_object
{
	int				type;
	t_matrix		*t;
	t_matrix		*t_inv;
	t_matrix		*rgb;
	float			alpha;
	float			alpha;
}					t_object;

typedef enum e_object_type
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}					t_object_type;

typedef struct s_object_validator
{
	char			*id;
	char			*format;
	int				type;
}					t_object_validator;

t_object_validator	*get_validator(void);
bool				validate_line(char **av, char *format);

t_object			*create_object(void);
void				destroy_object(void *content);
bool				is_valid_float(char *s);
bool				is_valid_int(char *s);
bool				is_valid_rgb(char *s);
bool				is_valid_vector(char *s);
bool				is_triple(char *s, bool (*f)(char *));
char				*get_format_by_type(int type);

/* Parsers that return allocated values (caller must free) */
double				parse_float(char *s);
int					parse_int(char *s);
double				*parse_rgb(char *s);
double				*parse_vector(char *s);

/* Creator parsers (construct objects from token arrays) */
t_object			*parse_ambient(char *line);
t_object			*parse_camera(char *line);
t_object			*parse_light(char *line);
t_object			*parse_sphere(char *line);
t_object			*parse_plane(char *line);
t_object			*parse_cylinder(char *line);
t_object			*parse_square(char *line);
bool				parse_vector_to_matrix(t_matrix *m, char *s,
						void *(*f)(char *));
bool				parse_rgb_to_matrix(t_matrix *m, char *s,
						void *(*conv)(const char *));
#endif
