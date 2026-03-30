/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 20:29:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>

/* path_utils.c */
char	*path_get_dir(const char *filepath);

/* dynarray.c */
bool	dynarray_ensure(void **array, size_t count, size_t *cap, size_t elem_size);

/* Helper for int-based counts (legacy support) */
# define DYNARRAY_ENSURE_INT(arr, count_ptr, cap_ptr, elem_size) \
	({ \
		size_t _cnt = *(count_ptr); \
		size_t _cap = *(cap_ptr); \
		bool _ret = dynarray_ensure((void **)(arr), _cnt, &_cap, (elem_size)); \
		*(cap_ptr) = (int)_cap; \
		_ret; \
	})

#endif
