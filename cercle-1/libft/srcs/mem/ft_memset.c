/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:45 by abdali            #+#    #+#             */
/*   Updated: 2025/10/16 20:38:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *s, int c, unsigned int n)
{
	unsigned char	*str;
	unsigned char	byte;

	str = (unsigned char *)s;
	byte = (unsigned char)c;
	if (!str)
		return (str);
	while (n)
		str[n-- - 1] = byte;
	return (str);
}
