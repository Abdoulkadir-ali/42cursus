/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:57:40 by abdoali           #+#    #+#             */
/*   Updated: 2025/10/20 12:01:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char			*dst;
	unsigned int	i;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i])
		i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_linecut(const char *src, char **dst, int c)
{
	int	i;
	int	j;

	if (!src || !dst)
		return (-1);
	i = 0;
	while (src[i] && src[i] != (char)c)
		i++;
	if (src[i] == (char)c)
		i++;
	*dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!*dst)
		return (-1);
	j = 0;
	while (j < i)
	{
		(*dst)[j] = src[j];
		j++;
	}
	(*dst)[j] = '\0';
	if (src[i - 1] == (char)c)
		return (i);
	return (-1);
}

int	ft_get_fd(t_elements **fds, int fd, t_elements **curr)
{
	t_elements	*current;
	t_elements	*new;

	if (!fds || !curr)
		return (0);
	current = *fds;
	while (current && current->fd != fd)
		current = current->next;
	if (current)
	{
		*curr = current;
		return (1);
	}
	new = malloc(sizeof(t_elements));
	if (!new)
		return (0);
	new->fd = fd;
	new->data = NULL;
	new->next = *fds;
	*fds = new;
	*curr = new;
	return (1);
}

char	*ft_read_elements(t_element *begin)
{
	char		*result;
	char		*str;
	t_element	*temp;
	int			total_len;
	int			pos;

	if (!begin)
		return (NULL);
	total_len = 0;
	temp = begin;
	while (temp)
	{
		pos = 0;
		while (temp->str[pos])
			pos++;
		total_len += pos;
		temp = temp->next;
	}
	result = malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return (NULL);
	pos = 0;
	while (begin && begin->str)
	{
		str = begin->str;
		while (*str)
			result[pos++] = *str++;
		begin = begin->next;
	}
	result[pos] = '\0';
	return (result);
}

void	ft_lstclear(t_element **lst)
{
	t_element	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	ft_lstaddback(t_element **lst, char *str)
{
	t_element	*new;
	t_element	*temp;

	if (!lst || !str)
		return ;
	new = malloc(sizeof(t_element));
	if (!new)
	{
		free(str);
		return ;
	}
	new->str = str;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
