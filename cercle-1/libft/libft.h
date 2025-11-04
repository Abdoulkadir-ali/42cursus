/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:08:27 by abdali            #+#    #+#             */
/*   Updated: 2025/10/17 00:20:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

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

unsigned int		ft_strlen(const char *s);
unsigned int		ft_strlcat(char *dst, const char *src, unsigned int size);
unsigned int		ft_strlcpy(char *dst, const char *src, unsigned int size);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
int					ft_atoi(const char *s);

void				ft_bzero(void *s, unsigned int n);
void				*ft_calloc(unsigned int nmemb, unsigned int size);
void				*ft_memchr(void *s, int c, unsigned int n);
void				*ft_memrchr(void *s, int c, unsigned int n);
int					ft_memcmp(void *s1, void *s2, unsigned int n);
void				*ft_memcpy(void *d, void *s, unsigned int n);
void				*ft_memrcpy(void *d, void *s, unsigned int n);
void				*ft_memmove(void *d, const void *s, unsigned int n);
void				*ft_memset(void *s, int c, unsigned int n);

char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, char c);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, unsigned int n);
char				*ft_strnstr(const char *haystack, const char *needle,
						unsigned int len);
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

#endif