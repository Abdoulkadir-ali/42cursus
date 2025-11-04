/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:57:33 by abdoali           #+#    #+#             */
/*   Updated: 2025/10/20 12:00:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static void	*ft_remove_fd(t_elements **fds, int fd, char *ptr)
{
	t_elements	*curr;
	t_elements	*prev;

	if (ptr)
		free(ptr);
	if (!fds || !*fds)
		return (NULL);
	curr = *fds;
	prev = NULL;
	while (curr && curr->fd != fd)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return (NULL);
	if (prev)
		prev->next = curr->next;
	else
		*fds = curr->next;
	ft_lstclear(&curr->data);
	free(curr);
	return (NULL);
}

static int	process_leftover(t_elements *curr, char **result)
{
	char	*temp;
	char	*leftover;
	int		l;

	if (!curr->data || !curr->data->str || !curr->data->str[0])
		return (0);
	l = ft_linecut(curr->data->str, &temp, '\n');
	if (l == -1)
	{
		free(temp);
		return (0);
	}
	leftover = ft_strdup(curr->data->str + l);
	free(curr->data->str);
	curr->data->str = temp;
	temp = ft_read_elements(curr->data);
	ft_lstclear(&curr->data);
	if (leftover && leftover[0])
		ft_lstaddback(&curr->data, leftover);
	else
		free(leftover);
	*result = temp;
	return (1);
}

static char	*handle_eof(t_elements **fds, t_elements *curr, char *buf)
{
	char	*result;

	if (buf)
		free(buf);
	result = ft_read_elements(curr->data);
	ft_lstclear(&curr->data);
	if (!result || !*result)
		return (ft_remove_fd(fds, curr->fd, result));
	ft_remove_fd(fds, curr->fd, NULL);
	return (result);
}

static int	process_buffer(t_elements *curr, char *buf, char **result, int b)
{
	char	*temp;
	int		l;

	buf[b] = '\0';
	l = ft_linecut(buf, &temp, '\n');
	ft_lstaddback(&curr->data, temp);
	if (l != -1)
	{
		*result = ft_read_elements(curr->data);
		ft_lstclear(&curr->data);
		if (buf[l])
			ft_lstaddback(&curr->data, ft_strdup(buf + l));
		free(buf);
		return (1);
	}
	free(buf);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_elements	*fds;
	t_elements			*curr;
	char				*buf;
	char				*result;
	int					bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_get_fd(&fds, fd, &curr))
		return (NULL);
	if (process_leftover(curr, &result))
		return (result);
	while (1)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_remove_fd(&fds, fd, buf));
		if (!bytes)
			return (handle_eof(&fds, curr, buf));
		if (process_buffer(curr, buf, &result, bytes))
			return (result);
	}
}
