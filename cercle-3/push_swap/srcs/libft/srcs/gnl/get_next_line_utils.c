/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:13:14 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 17:28:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strldup(char *str, int l)
{
	char	*r;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	while (*str && i < l)
		r[i++] = *str++;
	r[i] = 0;
	return (r);
}

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

char	*ft_free_gnl(char **fds, int fd)
{
	if (fds[fd])
	{
		free(fds[fd]);
		fds[fd] = NULL;
	}
	return (NULL);
}
