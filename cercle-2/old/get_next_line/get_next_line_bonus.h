/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:57:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/10/20 11:14:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_element
{
	char				*str;
	struct s_element	*next;
}						t_element;

typedef struct s_elements
{
	int					fd;
	t_element			*data;
	struct s_elements	*next;
}						t_elements;

char					*get_next_line(int fd);
int						ft_get_fd(t_elements **fds, int fd, t_elements **curr);
char					*ft_read_elements(t_element *begin);
void					ft_lstaddback(t_element **begin, char *str);
void					ft_lstclear(t_element **lst);
int						ft_linecut(const char *src, char **dst, int c);
char					*ft_strdup(const char *src);

#endif