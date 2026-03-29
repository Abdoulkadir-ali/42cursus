/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 17:16:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
void	build_light_sliders(t_light *lt, t_islider *sl, int *count)
{
	int	i;

	(void)lt;
	i = 0;
	while (g_props_light[i])
	{
		sl[i] = (t_islider){g_props_light[i]->name, g_props_light[i]->min,
			g_props_light[i]->max, NULL, g_props_light[i]};
		i++;
	}
	*count = i;
}
