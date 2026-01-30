/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:35:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 05:37:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	destroy_object(void *content)
{
	t_object	*obj;

	obj = (t_object *)content;
	if (!obj)
		return ;
	free_matrix(obj->t);
	free_matrix(obj->t_inv);
	free_matrix(obj->rgb);
	free(obj);
}
