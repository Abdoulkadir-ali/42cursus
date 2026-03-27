/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:56:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:01:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

# include "debug.h"
# include "maths.h"
# include "libft.h"

bool						dynarray_ensure(void **array, size_t count,
								size_t *cap, size_t elem_size);
bool						dynarray_ensure_int_impl(void **arr,
								int *count_ptr, int *cap_ptr, size_t elem_size);
# define DYNARRAY_ENSURE_INT(arr, count, cap, size) \
	dynarray_ensure_int_impl((void **)(arr), (count), (cap), (size))

const char					*get_file_extension(const char *path);

#endif