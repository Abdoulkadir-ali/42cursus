/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:23:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "gui.h"

void	build_light_sliders(t_light *lt, t_islider *sl, int *count)
{
	int	i;

	i = 0;
	sl[i++] = (t_islider){"Intensity", SL_INTENSITY_MIN, SL_INTENSITY_MAX,
		&lt->brightness};
	sl[i++] = (t_islider){"Color R", SL_COL_MIN, SL_COL_MAX, &lt->rgb.x};
	sl[i++] = (t_islider){"Color G", SL_COL_MIN, SL_COL_MAX, &lt->rgb.y};
	sl[i++] = (t_islider){"Color B", SL_COL_MIN, SL_COL_MAX, &lt->rgb.z};
	if (lt->type == LIGHT_SPOT)
		sl[i++] = (t_islider){"Cutoff (deg)", SL_CUTOFF_MIN, SL_CUTOFF_MAX,
			&lt->cutoff};
	*count = i;
}
