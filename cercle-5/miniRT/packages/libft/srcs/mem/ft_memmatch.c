/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:29:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 17:42:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	full_match(const void *sv, const void *sepv)
{
	const unsigned char	*s;
	size_t				sep_len;
	size_t				i;

	s = (const unsigned char *)sv;
	if (!s || !sepv)
		return (0);
	sep_len = ft_strlen((const char *)sepv);
	if (sep_len == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		if (ft_memcmp((void *)&s[i], (void *)sepv, sep_len) == 0)
			break ;
		i++;
	}
	return (i);
}

size_t	any_match(const void *sv, const void *sepv)
{
	const unsigned char	*s;
	size_t				sep_len;
	size_t				i;

	s = (const unsigned char *)sv;
	if (!s || !sepv)
		return (0);
	sep_len = ft_strlen((const char *)sepv);
	i = 0;
	while (s[i] && !ft_memchr((void *)sepv, s[i], sep_len))
		i++;
	return (i);
}
