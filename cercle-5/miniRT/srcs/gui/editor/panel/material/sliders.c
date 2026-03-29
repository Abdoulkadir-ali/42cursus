/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:50:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 17:22:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	build_mat_sliders(t_material *mat, t_islider *sl, int *count)
{
	int	i;
	int	j;

	(void)mat;
	i = 0;
	j = 0;
	while (g_props_material[j])
	{
		sl[i] = (t_islider){g_props_material[j]->name,
			g_props_material[j]->min,
			g_props_material[j]->max,
			NULL, g_props_material[j]};
		i++;
		j++;
	}
	*count = i;
}
