/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_cache.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:43:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 19:52:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEX_CACHE_H
# define TEX_CACHE_H

# include "libft.h"
# include "maths.h"
# include <stdlib.h>

typedef struct s_cached_tex
{
	char				*path;
	unsigned int		*data;
	t_vec2s				size;
	struct s_cached_tex	*next;
}						t_cached_tex;

typedef struct s_tex_cache
{
	t_cached_tex		*head;
}						t_tex_cache;

/*
** Texture Cache API
*/
t_cached_tex			*tex_cache_get(t_tex_cache *cache, const char *path);
int						tex_cache_add(t_tex_cache *cache, const char *path,
							unsigned int *data, t_vec2s size);
void					tex_cache_free(t_tex_cache *cache);

#endif
