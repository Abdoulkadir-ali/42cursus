/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:37 by abdali            #+#    #+#             */
/*   Updated: 2025/10/16 20:38:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memrchr(void *s, int c, unsigned int n)
{
	unsigned char	*str;
	unsigned char	byte;

	str = (unsigned char *)s;
	byte = (unsigned char)c;
	while (n)
	{
		if (str[n - 1] == byte)
			return (&str[n - 1]);
		n--;
	}
	return ((void *)0);
}
