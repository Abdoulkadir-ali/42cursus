/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:08:27 by abdali            #+#    #+#             */
/*   Updated: 2026/03/25 14:29:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FDS
#  define MAX_FDS 1024
# endif

/* Flags structure for bonus handling */
typedef struct s_flags
{
	bool			minus;
	bool			zero;
	bool			hash;
	bool			space;
	bool			plus;
	int				width;
	int				precision;
	bool			has_precision;
	char			type;
	int				fd;
}					t_flags;

typedef struct s_printf
{
	int				i;
	size_t			count;
	int				fd;
}					t_printf;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_nodes;

typedef struct s_buffer
{
	char			*data;
	size_t			len;
	size_t			cap;
}					t_buffer;

typedef struct s_stack
{
	void			**items;
	size_t			size;
	size_t			cap;
}					t_stack;

bool				ft_isalpha(int c);
bool				ft_isalnum(int c);
bool				ft_isascii(int c);
bool				ft_isdigit(int c);
bool				ft_isprint(int c);
char				ft_tolower(char c);
char				ft_toupper(char c);
bool				ft_isspace(char c);
int					ft_strrchri(char *str, char c);
int					ft_strchri(char *str, char c);

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

long long			ft_atoll(const char *str);
long long			ft_safe_atoll(const char *str, bool *error);

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
char				*ft_strldup(char *str, size_t l);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start,
						unsigned int len);

bool				ft_check_base(const char *base);
size_t				ft_nbrlen_base(long long int n, size_t base);
size_t				ft_unbrlen_base(unsigned long long int n, size_t base);
size_t				ft_putnbr_base(long long int n, const char *base, int fd);
size_t				ft_putunbr_base(unsigned long long int n, const char *base,
						int fd);
char				*ft_itoa_base(long long int n, const char *base);
long long int		ft_atoi_base(const char *str, const char *base);

t_nodes				*ft_lstnew(void *content);
void				ft_lstadd_front(t_nodes **lst, t_nodes *new);
size_t				ft_lstsize(t_nodes *lst);
t_nodes				*ft_lstlast(t_nodes *lst);
void				ft_lstadd_back(t_nodes **lst, t_nodes *new);
void				ft_lstdelone(t_nodes *lst, void (*del)(void *));
void				ft_lstclear(t_nodes **lst, void (*del)(void *));
void				ft_lstiter(t_nodes *lst, void (*f)(void *));
t_nodes				*ft_lstmap(t_nodes *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstsort(t_nodes **lst, int (*cmp)(void *, void *));

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
int					ft_print_width(int width, int zero, int left, int fd);
int					ft_count_digits(long n);
int					ft_count_hex_digits(unsigned long n);
int					ft_print_number_with_flags(long n, t_flags *flags);
int					ft_print_unsigned_with_flags(unsigned int n,
						t_flags *flags);
int					ft_print_hex_with_flags(unsigned long n, t_flags *flags);
int					ft_print_string_with_flags(char *str, t_flags *flags);
int					ft_print_sign_and_prefix(long n, t_flags *flags,
						int *sign_printed);
int					ft_print_precision_zeros(int num_len, int precision,
						int fd);

int					ft_printf(const char *format, ...);
int					ft_printf_fd(int fd, const char *format, ...);
int					ft_vprintf_fd(int fd, const char *format, va_list args);
void				ft_puterror_header(const char *header, const char *fmt,
						...);
void				ft_puterror_fmt(const char *fmt, ...);
void				ft_vputerror_fd(int fd, const char *fmt, va_list args);
void				ft_vputerror_header_fd(int fd, const char *header,
						const char *fmt, va_list args);

/* Buffer helpers: simple dynamic byte buffer for building strings/data */
t_buffer			*ft_buffer_new(size_t initial);
void				ft_buffer_free(t_buffer *b);
int					ft_buffer_reserve(t_buffer *b, size_t additional);
int					ft_buffer_append(t_buffer *b, const char *s, size_t n);
int					ft_buffer_append_str(t_buffer *b, const char *s);
int					ft_buffer_append_char(t_buffer *b, char c);
char				*ft_buffer_to_string(t_buffer *b);

t_stack				*ft_stack_new(void);
void				ft_stack_free(t_stack *s, void (*del)(void *));
int					ft_stack_push(t_stack *s, void *item);
void				*ft_stack_pop(t_stack *s);
void				*ft_stack_peek(t_stack *s);
int					ft_stack_reserve(t_stack *s, size_t additional);
size_t				ft_stack_size(t_stack *s);

#endif