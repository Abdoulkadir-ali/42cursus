/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 03:49:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include "libft.h"
# include "maths.h"

struct s_app;

int		parse_file(const char *path, struct s_app *app);
int		tokenize(char *line, char **tokens, int max_tokens);
int		parse_color(const char *s, t_vec3 *out);
int		parse_vec3(const char *s, t_vec3 *out);
int		parse_unit_vec3(const char *s, t_vec3 *out);
char	*read_file_all(const char *path);
int		is_file_imported(const char *path);
void	cache_imported_file(const char *path);

const char	*json_skip_ws(const char *p, const char *end);
const char	*json_skip_value(const char *p, const char *end);
const char	*json_obj_find(const char *p, const char *end, const char *key);
const char	*json_arr_get(const char *p, const char *end, int n);
int			json_count_array(const char *p, const char *end);
int			json_arr_len(const char *p, const char *end);
long		json_int(const char *p, const char *end);
long		json_int_idx(const char *p, const char *end, int i);
double		json_flt(const char *p, const char *end);
double		json_flt_idx(const char *p, const char *end, int i);
int			json_streq(const char *p, const char *end, const char *s);
void		json_str_copy(const char *p, const char *end, char *dst, int max);

#endif
