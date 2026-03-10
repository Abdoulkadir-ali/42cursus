/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:27:14 by abdali            #+#    #+#             */
/*   Updated: 2025/11/10 21:59:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_handle_special_cases(long long int n, const char *base)
{
	int	n_len;

	if (n == LLONG_MIN)
	{
		write(1, "-9223372036854775808", 20);
		return (20);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n_len = ft_putnbr_base(-n, base) + 1;
		return (n_len);
	}
	return (-1);
}

int	ft_putnbr_base(long long int n, const char *base)
{
	int	base_len;
	int	n_len;
	int	special;

	if (!ft_check_base(base))
		return (0);
	base_len = ft_strlen(base);
	special = ft_handle_special_cases(n, base);
	if (special != -1)
		return (special);
	if (n >= base_len)
	{
		ft_putnbr_base(n / base_len, base);
		ft_putnbr_base(n % base_len, base);
	}
	else
		write(1, &base[n], 1);
	n_len = ft_nbrlen_base(n, base_len);
	return (n_len);
}
