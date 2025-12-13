/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:32:34 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 18:36:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_memset_handle_small(char **p, unsigned char byte, size_t *n)
{
	while (*n--)
		*(*p)++ = byte;
}

static void	ft_memset_handle_align(char **p, unsigned char byte, size_t *n)
{
	size_t	alignment_offset;
	size_t	leading_bytes;

	alignment_offset = (uintptr_t)(*p) % sizeof(uint64_t);
	if (!alignment_offset)
		return ;
	leading_bytes = sizeof(uint64_t) - alignment_offset;
	while (leading_bytes-- && *n)
	{
		*(*p)++ = byte;
		(*n)--;
	}
}

static void	ft_memset_bulk(char **p, unsigned char byte, size_t *n)
{
	uint64_t	word_val;
	uint64_t	*aligned_p;
	size_t		bulk_words;

	word_val = byte;
	word_val |= (word_val << 8);
	word_val |= (word_val << 16);
	word_val |= (word_val << 32);
	aligned_p = (uint64_t *)*p;
	bulk_words = *n / sizeof(uint64_t);
	while (bulk_words--)
		*aligned_p++ = word_val;
	*p = (char *)aligned_p;
	*n %= sizeof(uint64_t);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char			*p;
	unsigned char	byte;
	void			*original_s;

	original_s = s;
	p = (char *)s;
	byte = (unsigned char)c;
	if (n < 8)
	{
		ft_memset_handle_small(&p, byte, &n);
		return (original_s);
	}
	ft_memset_handle_align(&p, byte, &n);
	ft_memset_bulk(&p, byte, &n);
	ft_memset_handle_small(&p, byte, &n);
	return (original_s);
}
