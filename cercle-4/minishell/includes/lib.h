#ifndef LIB_H
# define LIB_H

# include <stdarg.h>
# include <stdio.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

void	debug_printf(const char *format, ...);

int		ft_strmatch(char *s1, char *s2, int (*match)(char *, char *));
int		str_any(char *s1, char *s2);

#endif
