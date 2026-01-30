/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/30 18:04:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_nodes_get(t_nodes *list, size_t n)
{
	size_t	i;
	t_nodes	*cur;

	if (!list)
		return (NULL);
	cur = list;
	i = 0;
	while (cur && i < n)
	{
		cur = cur->next;
		i++;
	}
	if (!cur)
		return (NULL);
	return ((char *)cur->content);
}
