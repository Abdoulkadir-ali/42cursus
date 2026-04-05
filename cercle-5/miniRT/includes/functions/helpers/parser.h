/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 12:49:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <dirent.h>
# include <fcntl.h>
# include "helpers.h"
# include "types.h"

typedef struct s_json_value t_json_value;

typedef struct s_json_member
{
	char				*key;
	t_json_value		*value;
}						t_json_member;

typedef struct s_json_hash_entry
{
	char				*key;
	t_json_value		*value;
	struct s_json_hash_entry	*next;
}						t_json_hash_entry;

typedef struct s_json_object
{
	t_json_member		**members;
	t_json_hash_entry	**hashmap;
	size_t				count;
	size_t				hash_size;
}						t_json_object;

typedef struct s_json_array
{
	t_json_value		**elements;
	size_t				count;
	size_t				cap;
}						t_json_array;

struct s_json_value
{
	t_json_type			type;
	union
	{
		bool			boolean;
		double			number;
		char			*string;
		t_json_array	array;
		t_json_object	object;
	}					u;
};

/* Core Parser Functions */
void					parser_init(t_parser *p, int fd);
char					parser_peek(t_parser *p);
void					parser_advance(t_parser *p);
void					parser_skip_spaces(t_parser *p);
bool					parser_match(t_parser *p, char expected);
bool					parser_get_line(t_parser *p, char *buf,
							size_t max_len);

/* Extractors */
int						parse_int(t_parser *p);
double					parse_double(t_parser *p);
bool					parse_vec3(t_parser *p, t_vec3 *out);

/* JSON API */
t_json_value			*json_parse(const char *json_str);
t_json_value			*json_parse_len(const char *json_str, size_t len);
void					json_free(t_json_value *value);
t_json_value			*json_get(t_json_value *value, const char *key);
t_json_value			*json_at(t_json_value *value, size_t index);
const char				*json_as_string(t_json_value *value);
double					json_as_number(t_json_value *value);
bool					json_as_bool(t_json_value *value);
int						json_get_int(t_json_value *obj, const char *key);
t_index					json_get_size_t(t_json_value *obj, const char *key);
t_index					json_as_t_index(t_json_value *value);
void					*json_realloc(void *ptr, size_t old_size,
							size_t new_size);
void					*json_malloc(size_t size);
void					json_skip_ws(const char **s);
t_json_value			*json_parse_inner_value(const char **s);
t_json_value			*json_parse_inner_object(const char **s);
t_json_value			*json_parse_inner_array(const char **s);
t_json_value			*json_parse_inner_number(const char **s);
char					*json_parse_inner_string(const char **s);
void					json_hash_insert(t_json_object *obj, char *key,
							t_json_value *val);
size_t					json_hash_key(const char *key, size_t size);

#endif
