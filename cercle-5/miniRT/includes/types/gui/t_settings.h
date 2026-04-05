/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_settings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 17:30:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SETTINGS_H
# define T_SETTINGS_H

# include <stdbool.h>
# include "t_maths.h"

typedef enum e_settings_tab
{
	STAB_WINDOW,
	STAB_PHYSICS,
	STAB_RAYTRACER
}	t_settings_tab;

typedef struct s_settings_panel
{
	bool			visible;
	t_settings_tab	tab;
	double			render_scale;	/* proxy for render.scale (size_t)    */
	double			solver_iters;	/* proxy for solver_iterations (size_t) */
	t_vec2i			pos;			/* top-left corner of the panel         */
	bool			dragging;		/* header is being dragged              */
	t_vec2i			drag_offset;	/* mouse offset from panel origin       */
}	t_settings_panel;

#endif
