/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:41 by abdali            #+#    #+#             */
/*   Updated: 2025/10/16 20:38:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memrcpy(void *d, void *s, unsigned int n)
{
	unsigned char	*dest;
	unsigned char	*src;

	dest = (unsigned char *)d;
	src = (unsigned char *)s;
	while (n)
	{
		dest[n - 1] = src[n - 1];
		n--;
	}
	return ((void *)dest);
}
