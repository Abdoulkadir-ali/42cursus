/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:30 by abdali            #+#    #+#             */
/*   Updated: 2025/10/16 20:38:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *d, void *s, unsigned int n)
{
	unsigned char	*dest;
	unsigned char	*src;
	unsigned int	i;

	dest = (unsigned char *)d;
	src = (unsigned char *)s;
	i = 0;
	while (i < n)
		dest[i++] = *src++;
	return ((void *)dest);
}
