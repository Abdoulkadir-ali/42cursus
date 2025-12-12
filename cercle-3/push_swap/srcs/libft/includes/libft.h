/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:08:27 by abdali            #+#    #+#             */
/*   Updated: 2025/12/12 17:28:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FDS
#  define MAX_FDS 4096
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);

size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *s);

void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(void *s, int c, size_t n);
void				*ft_memrchr(void *s, int c, size_t n);
int					ft_memcmp(void *s1, void *s2, size_t n);
void				*ft_memcpy(void *d, const void *s, size_t n);
void				*ft_memrcpy(void *d, const void *s, size_t n);
void				*ft_memmove(void *d, const void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);

char				*ft_itoa(int n);

void				*ft_free_split(char **strs);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start,
						unsigned int len);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

char				*ft_strldup(char *str, int l);
char				*ft_realloc(char *s1, char *s2);
char				*ft_free_buffer(char *buffer);
char				*extract_remainder(char *newline_pos);
char				*ft_free_gnl(char **fds, int fd);
char				*consume_line(char **fds, int fd);
char				*read_line(char **fds, int fd, char *buffer);
char				*get_next_line(int fd);

#endif