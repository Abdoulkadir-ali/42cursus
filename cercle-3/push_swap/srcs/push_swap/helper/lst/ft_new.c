/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:18:47 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 16:18:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_nodes	*ft_new(int value)
{
	t_nodes	*new;

	new = malloc(sizeof(t_nodes));
	if (!new)
		return (NULL);
	new->v = value;
	new->meta.index = 0;
	new->meta.push_cost = 0;
	new->meta.above_median = 0;
	new->meta.target = NULL;
	new->meta.is_cheapest = 0;
	new->next = NULL;
	return (new);
}
