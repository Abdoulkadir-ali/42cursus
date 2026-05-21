/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_to_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:17:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:29:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_buffer_to_string(t_buffer *b)
{
	char	*ret;

	if (!b)
		return (NULL);
	ret = malloc(b->len + 1);
	if (!ret)
		return (NULL);
	if (b->len)
		ft_memcpy(ret, b->data, b->len);
	ret[b->len] = '\0';
	return (ret);
}
