/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 17:52:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* POSIX / system */
# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

/* 1. NEUTRAL DEPENDENCIES */
# include "debug.h"

# define MAX_LEAF_OBJECTS 4
# define PARSER_BUF_SIZE 65536

/* JSON Parser (Robust) */

/* JSON / parser forward types */
typedef struct s_json_value			t_json_value;
typedef struct s_json_member		t_json_member;
typedef struct s_json_hash_entry	t_json_hash_entry;
typedef struct s_json_array			t_json_array;
typedef struct s_json_object		t_json_object;

typedef enum e_json_type
{
	JSON_NULL,
	JSON_BOOL,
	JSON_NUMBER,
	JSON_STRING,
	JSON_ARRAY,
	JSON_OBJECT
}									t_json_type;

typedef struct s_parser
{
	int								fd;
	char							buffer[PARSER_BUF_SIZE + 1];
	size_t							cursor;
	size_t							bytes_read;
	bool							eof;
}									t_parser;

typedef struct s_json_member
{
	char							*key;
	t_json_value					*value;
}									t_json_member;

typedef struct s_json_hash_entry
{
	char							*key;
	t_json_value					*value;
	struct s_json_hash_entry		*next;
}									t_json_hash_entry;

typedef struct s_json_object
{
	t_json_member					**members;
	t_json_hash_entry				**hashmap;
	size_t							count;
	size_t							hash_size;
}									t_json_object;

typedef struct s_json_array
{
	t_json_value					**elements;
	size_t							count;
	size_t							cap;
}									t_json_array;

typedef struct s_json_value
{
	t_json_type						type;
	union
	{
		bool						boolean;
		double						number;
		char						*string;
		t_json_array				array;
		t_json_object				object;
	};
}									t_json_value;

char								*path_get_dir(const char *filepath);

t_json_value						*json_parse(const char *json_str);
void								json_free(t_json_value *value);

/* JSON Query Helpers */
t_json_value						*json_get(t_json_value *value,
										const char *key);
t_json_value						*json_at(t_json_value *value, size_t index);
const char							*json_as_string(t_json_value *value);
double								json_as_number(t_json_value *value);
bool								json_as_bool(t_json_value *value);
int									json_get_int(t_json_value *obj,
										const char *key);

void								json_skip_ws(const char **s);
size_t								json_hash_key(const char *key, size_t size);
void								*json_realloc(void *ptr, size_t old_size,
										size_t new_size);
void								json_hash_insert(t_json_object *obj,
										char *key, t_json_value *val);
char								*json_parse_inner_string(const char **s);
t_json_value						*json_parse_inner_object(const char **s);
t_json_value						*json_parse_inner_array(const char **s);
t_json_value						*json_parse_inner_number(const char **s);
t_json_value						*json_parse_inner_value(const char **s);

/* Core functions */
void								parser_init(t_parser *p, int fd);
char								parser_peek(t_parser *p);
void								parser_advance(t_parser *p);
void								parser_skip_spaces(t_parser *p);
bool								parser_match(t_parser *p, char expected);
bool								parser_get_line(t_parser *p, char *buf,
										size_t max_len);

/* Extractors */
int									parse_int(t_parser *p);
double								parse_double(t_parser *p);
bool								parse_vec3(t_parser *p, t_vec3 *out);

struct s_sub_shape					parse_brick(t_json_value *obj);
struct s_physics_body				parse_compound_body(t_json_value *obj);

#endif