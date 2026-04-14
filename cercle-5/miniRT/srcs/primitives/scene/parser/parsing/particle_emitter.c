/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_emitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 10:57:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/*
** Parses a particle emitter line:
**
**   pe <x,y,z>  <dx,dy,dz>  <rate>  <speed>
**      <life_min>  <life_max>  <size>
**      [spread]  [temp_min]  [temp_max]
**
**   pos     : world position of the emitter
**   dir     : launch direction (need not be normalised; we normalise it)
**   rate    : particles per second
**   speed   : launch speed in scene units / second
**   life_min/max: lifetime range in seconds
**   size    : proxy sphere radius in scene units
**   spread  : cone half-angle (radians) — default 0.15 (~8.6°)
**   temp_min/max: birth temperature [0,1] — default 0.6 / 1.0
*/
static void	parse_pe_optional(t_parser *p, t_emitter *em)
{
	em->spread = parse_double(p);
	if (em->spread < 1e-9)
		em->spread = 0.15;
	em->temp_min = parse_double(p);
	if (em->temp_min < 1e-9)
		em->temp_min = 0.6;
	em->temp_max = parse_double(p);
	if (em->temp_max < 1e-9)
		em->temp_max = 1.0;
}

t_parse_obj	parse_particle_emitter(t_parser *p)
{
	t_parse_obj	res;
	t_emitter	em;

	ft_memset(&res, 0, sizeof(res));
	ft_memset(&em, 0, sizeof(em));
	res.type = TYPE_NONE;
	if (!parse_vec3(p, &em.pos) || !parse_vec3(p, &em.dir))
		return (res);
	em.rate = parse_double(p);
	em.speed = parse_double(p);
	em.life_min = parse_double(p);
	em.life_max = parse_double(p);
	em.size = parse_double(p);
	parse_pe_optional(p, &em);
	em.shape = EMITTER_CONE;
	em.active = true;
	res.data.emitter = em;
	res.type = TYPE_PARTICLE_EMITTER;
	return (res);
}
