/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:53:04 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:58:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
#define LIB_H

/* 1. STANDARD C HEADERS */
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include "mlx.h"
# include "stb_image.h"

static inline int	mlx_string_put_c(void *m, void *w, int x, int y,
					int c, const char *s)
{
	return (mlx_string_put(m, w, x, y, c, (char *)s));
}
# define mlx_string_put	mlx_string_put_c

/* 2. BASE PACKAGES */
# include "libft.h"
# include "types.h"

#endif
