/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STB_H
# define STB_H

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

# include "../packages/stb_image.h"

# pragma GCC diagnostic pop

#endif
