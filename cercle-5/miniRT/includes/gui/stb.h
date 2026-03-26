/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 09:35:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STB_H
# define STB_H
/* External dependencies */
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

/*
** Wrapper for STB Image library to centralize dependency path
** and suppress common warnings coming from the library itself.
*/

# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
# pragma GCC diagnostic ignored "-Wunused-parameter"
# pragma GCC diagnostic ignored "-Wmissing-field-initializers"
# pragma GCC diagnostic ignored "-Wsign-compare"
# pragma GCC diagnostic ignored "-Wtype-limits"

/* zlib may be used by the bundled STB PNG decoder; include when available */
# include <zlib.h>

# include "../packages/stb_image.h"

# pragma GCC diagnostic pop

#endif
