/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:27:14 by abdali            #+#    #+#             */
/*   Updated: 2026/01/11 13:16:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs data explicitly to the specified descriptor/stdout.
 * 
 * @param n Target structural variable.
 * @param base Target structural variable.
 * @param fd Target structural variable.
 * @return size_t output natively.
 */
size_t	ft_putunbr_base(unsigned long long int n, const char *base, int fd)
{
	size_t	base_len;
	size_t	nbr_len;

	if (!ft_check_base(base))
		return (0);
	nbr_len = 0;
	base_len = ft_strlen(base);
	if (n >= base_len)
	{
		ft_putunbr_base(n / base_len, base, fd);
		ft_putunbr_base(n % base_len, base, fd);
	}
	else
		write(fd, &base[n], 1);
	nbr_len += ft_unbrlen_base(n, base_len);
	return (nbr_len);
}
