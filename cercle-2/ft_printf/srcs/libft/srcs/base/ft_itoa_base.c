/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/04 11:01:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long int n, const char *base)
{
	char	*str;
	int		len;
	int		base_len;
	int		is_negative;

	if (!ft_check_base(base))
		return (NULL);
	base_len = ft_strlen(base);
	is_negative = (n < 0);
	if (is_negative)
		n = -n;
	len = ft_nbrlen_base(n, base_len) + is_negative;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > is_negative)
	{
		str[len] = base[n % base_len];
		n /= base_len;
	}
	if (is_negative)
		str[0] = '-';
	return (str);
}
