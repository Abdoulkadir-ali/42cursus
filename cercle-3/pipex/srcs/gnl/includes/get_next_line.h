/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:13:23 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 16:55:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../../libft/includes/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FDS
#  define MAX_FDS 4096
# endif

char	*ft_strldup(char *str, int l);
char	*ft_realloc(char *s1, char *s2);
char	*ft_free_buffer(char *buffer);
char	*extract_remainder(char *buffer, int newline_pos);
char	*gnl_free(char **fds, int fd);
char	*consume_line(char **fds, int fd);
char	*read_line(char **fds, int fd, char *buffer);
char	*get_next_line(int fd);

#endif