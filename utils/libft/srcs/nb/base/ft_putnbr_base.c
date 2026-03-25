/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:27:14 by abdali            #+#    #+#             */
/*   Updated: 2026/03/25 14:11:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Handles special cases for negative numbers and LLONG_MIN.
 * @note Internal helper function.
 */
static size_t	ft_handle_special_cases(long long int n, const char *base,
		int fd)
{
	size_t	n_len;

	if (n == LLONG_MIN)
	{
		write(fd, "-9223372036854775808", 20);
		return (20);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n_len = ft_putnbr_base(-n, base, fd) + 1;
		return (n_len);
	}
	return (0);
}

/**
 * @brief Outputs data explicitly to the specified descriptor/stdout.
 *
 * @param n Target structural variable.
 * @param base Target structural variable.
 * @param fd Target structural variable.
 * @return size_t output natively.
 */
size_t	ft_putnbr_base(long long int n, const char *base, int fd)
{
	size_t	base_len;
	size_t	n_len;
	size_t	special;

	if (!ft_check_base(base))
		return (0);
	base_len = ft_strlen(base);
	special = ft_handle_special_cases(n, base, fd);
	if (special != 0)
		return (special);
	if (n >= (long long int)base_len)
	{
		ft_putnbr_base(n / base_len, base, fd);
		ft_putnbr_base(n % base_len, base, fd);
	}
	else
		write(fd, &base[n], 1);
	n_len = ft_nbrlen_base(n, base_len);
	return (n_len);
}
