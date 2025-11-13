/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:08:27 by abdali            #+#    #+#             */
/*   Updated: 2025/11/13 13:19:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FDS
#  define MAX_FDS 1024
# endif

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

/* Flags structure for bonus handling */
typedef struct s_flags
{
	int				minus;
	int				zero;
	int				hash;
	int				space;
	int				plus;
	int				width;
	int				precision;
	int				has_precision;
	char			type;
}					t_flags;

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
char				*ft_strcpy(char *dst, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *s);
void				ft_swap(int *a, int *b);

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
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
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

int					ft_check_base(const char *base);
size_t				ft_nbrlen_base(long long int n, size_t base);
size_t				ft_unbrlen_base(unsigned long long int n, size_t base);
int					ft_putnbr_base(long long int n, const char *base);
int					ft_putunbr_base(unsigned long long int n, const char *base);
char				*ft_itoa_base(long long int n, const char *base);
long long int		ft_atoi_base(const char *str, const char *base);

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

char				*get_next_line(int fd);
int					gnl_strchr_idx(char *str, char c);
char				*gnl_realloc(char *s1, char *s2);
char				*gnl_free(char **fds, int fd);

int					ft_handle_char(va_list args, t_flags *flags);
int					ft_handle_string(va_list args, t_flags *flags);
int					ft_handle_number(va_list args, t_flags *flags);
int					ft_handle_hex(va_list args, t_flags *flags);
int					ft_handle_pointer(va_list args, t_flags *flags);

int					ft_parse_flags(const char *format, int *i, t_flags *flags);
int					ft_print_width(int width, int zero, int left);
int					ft_count_digits(long n);
int					ft_count_hex_digits(unsigned long n);
int					ft_print_number_with_flags(long n, t_flags *flags);
int					ft_print_unsigned_with_flags(unsigned int n,
						t_flags *flags);
int					ft_print_hex_with_flags(unsigned long n, t_flags *flags);
int					ft_print_string_with_flags(char *str, t_flags *flags);
int					ft_print_sign_and_prefix(long n, t_flags *flags,
						int *sign_printed);
int					ft_print_precision_zeros(int num_len, int precision);

int					ft_printf(const char *format, ...);

#endif