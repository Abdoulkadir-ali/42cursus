/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:27:14 by abdali            #+#    #+#             */
/*   Updated: 2025/10/22 22:59:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	total_len;

	if ((!dst || !src) && size == 0)
		return (0);
	dest_len = ft_strlen(dst);
	if (dest_len < size)
		total_len = dest_len + ft_strlen(src);
	else
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] && (dest_len + i + 1) < size)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[i + dest_len] = '\0';
	return (total_len);
}
