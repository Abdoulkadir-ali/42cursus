/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 05:23:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 19:31:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "maths.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_properties
{
	char			*id;
	void			*v;
}					t_properties;

typedef struct s_transform
{
	t_matrix		*pos;
	t_matrix		*rotation;
	t_matrix		*scale;
}					t_transform;

typedef struct t_object
{
	int				type;
	t_transform		*transform;
	t_matrix		*rgb;
	t_nodes			*attrs;
}					t_object;

typedef enum e_object_type
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	SQUARE,
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
bool				validate_line_nodes(t_nodes *av, char *format);

t_object			*create_object(void);
void				destroy_object(void *content);

/* Matrix initializers */
t_transform			*init_transform(void);
void				free_transform(t_transform *t);
t_matrix			*init_rgb(void);

bool				is_valid_float(const char *s);
bool				is_valid_int(const char *s);
bool				is_valid_rgb(const char *s);
bool				is_valid_vector(const char *s);
bool				is_triple(const char *s, bool (*f)(const char *));
char				*get_format_by_type(int type);

/* Parsers that return allocated values (caller must free) */
double				parse_float(const char *s);
int					parse_int(char *s);
// Removed duplicate declarations for parse_rgb and parse_vector

/* Creator parsers (construct objects from token arrays) */
t_object			*parse_ambient(char *line);
t_object			*parse_camera(char *line);
t_object			*parse_light(char *line);
t_object			*parse_sphere(char *line);
t_object			*parse_plane(char *line);
t_object			*parse_cylinder(char *line);
t_object			*parse_square(char *line);

/* parsing helpers exposed for tests */
bool				parse_file(const char *path);
t_object			*parse_line(char *line);
void				print_object(t_object *obj);

bool				parse_vector(t_matrix *m, char *s,
						double *(*f)(const char *));
bool				parse_normal_to_matrix(t_matrix *m, char *s,
						double (*conv)(const char *));
bool				parse_rgb(t_matrix *m, char *s, bool (*conv)(const char *));
#endif
