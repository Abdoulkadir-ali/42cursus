/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:07:24 by abdali            #+#    #+#             */
/*   Updated: 2026/03/25 14:10:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Returns a pointer to the last occurrence of
 * the character c in the string s.
 * @note Public library exported function.
 */
char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = (char *)0;
	while (*s)
	{
		if (*s == (char)c)
			last = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (last);
}
