/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:51:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/10 23:51:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Executes public ft_realloc utility.
 * @note Public library exported function.
 */
char	*ft_realloc(char *s1, char *s2)
{
	char	*res;
	char	*temp;
	int		total_len;
	int		i;

	i = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (total_len + 1));
	if (!res)
		return (NULL);
	temp = s1;
	while (temp && *temp)
		res[i++] = *temp++;
	temp = s2;
	while (temp && *temp)
		res[i++] = *temp++;
	res[i] = 0;
	if (s1)
		free(s1);
	return (res);
}
