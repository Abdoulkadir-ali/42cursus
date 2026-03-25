/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_append_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:16:59 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 14:28:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_buffer_append_str(t_buffer *b, const char *s)
{
	size_t	n;

	if (!s)
		return (0);
	n = ft_strlen(s);
	return (ft_buffer_append(b, s, n));
}
