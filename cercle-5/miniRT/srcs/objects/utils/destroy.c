/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:35:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:23:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	destroy_object(void *content)
{
	t_object	*obj;

	obj = (t_object *)content;
	if (!obj)
		return ;
	if (obj->transform)
	{
		free_matrix(obj->transform->pos, NULL);
		free_matrix(obj->transform->rotation, NULL);
		free_matrix(obj->transform->scale, NULL);
		free(obj->transform);
	}
	free_matrix(obj->rgb, NULL);
	free(obj);
}
