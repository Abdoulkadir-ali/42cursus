/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 05:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/**
 * @brief Allocates and copies an array for the scene snapshot.
 */
void	snap_array(void **dst, void *src, int count, size_t sz)
{
	*dst = NULL;
	if (count <= 0)
		return ;
	*dst = malloc(count * sz);
	if (*dst)
		ft_memcpy(*dst, src, (size_t)count * sz);
}
