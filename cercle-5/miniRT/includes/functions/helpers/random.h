/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 15:18:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_RANDOM_H
# define HELPERS_RANDOM_H

# include "types.h"

/*
** srcs/helpers/random/seed.c
** rt_seed_pos  : Murmur3-finalized hash of position only (cache once per hit).
** rt_seed_mix  : XORs cached base with frame+id (cheap, call per sample).
** rt_seed_point: convenience wrapper (pos + mix in one call).
*/
uint32_t	rt_seed_pos(t_vec3 p);
uint32_t	rt_seed_mix(uint32_t base, int frame, int id);
uint32_t	rt_seed_point(t_vec3 p, int frame, int id);

#endif
