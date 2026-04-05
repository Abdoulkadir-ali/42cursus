/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_animation.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 17:52:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ANIMATION_H
# define T_ANIMATION_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_anim_engine
{
	bool	enabled;
	double	time_scale;
	size_t	*mesh_indices;
	size_t	mesh_count;
}			t_anim_engine;

#endif
