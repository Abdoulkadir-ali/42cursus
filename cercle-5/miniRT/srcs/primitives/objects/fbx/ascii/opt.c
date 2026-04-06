/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

void	ascii_load_normals(t_fbx_ascii *asc)
{
	char	*temp;

	asc->rn = NULL;
	temp = find_node(asc->p, asc->end, "Normals:");
	if (!temp)
		return ;
	temp = advance_to_data(temp, asc->end);
	asc->rn = parse_array(&temp, &asc->nu.x, sizeof(t_vec3), f_vec3);
}

void	ascii_load_uvs(t_fbx_ascii *asc)
{
	char	*temp;

	asc->ru = NULL;
	temp = find_node(asc->p, asc->end, "UV:");
	if (!temp)
		return ;
	temp = advance_to_data(temp, asc->end);
	asc->ru = parse_array(&temp, &asc->nu.y, sizeof(t_vec2), f_vec2);
}
