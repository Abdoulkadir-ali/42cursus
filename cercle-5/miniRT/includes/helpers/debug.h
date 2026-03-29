/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:44:23 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/01 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/* STD lib */
# include <float.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

/* Standard C library */
# include "libft.h"

/* --- Debug active flag --- */
# define DEBUG 1

/* --- Legacy print macro (kept for compatibility) --- */
# if DEBUG
#  define ft_print_debug(...) (printf(__VA_ARGS__), fflush(stdout))
# else
#  define ft_print_debug(...) ((void)0)
# endif

/* --- Debug channels (bitmask) --- */
# define DBG_CH_NONE    0x00
# define DBG_CH_RENDER  0x01
# define DBG_CH_BVH     0x02
# define DBG_CH_PHYSICS 0x04
# define DBG_CH_PARSER  0x08
# define DBG_CH_EDITOR  0x10
# define DBG_CH_ANIM    0x20
# define DBG_CH_TEXTURE 0x40
# define DBG_CH_ALL     0xFF

/* --- Log levels --- */
# define DBG_ERR    0
# define DBG_WARN   1
# define DBG_INFO   2
# define DBG_TRACE  3

/* --- Compile-time defaults (override with -DDBG_CHANNELS=0x01 etc.) --- */
# ifndef DBG_CHANNELS
#  define DBG_CHANNELS  DBG_CH_ALL
# endif
# ifndef DBG_MAX_LEVEL
#  define DBG_MAX_LEVEL DBG_TRACE
# endif

/* --- Log file path --- */
# define DBG_LOG_PATH "/tmp/minirt_debug.log"

/* --- Core functions (srcs/helpers/debug/log.c) --- */
void    dbg_print(int ch, int lvl, const char *fmt, ...);
void    dbg_log_init(const char *path);
void    dbg_log_close(void);

/* --- Main macro --- */
# ifdef DEBUG
#  define DBG(ch, lvl, ...) \
	do { if (((ch) & DBG_CHANNELS) && (lvl) <= DBG_MAX_LEVEL) \
		dbg_print((ch), (lvl), __VA_ARGS__); } while (0)
#  define DBG_ENTER(fn)   DBG(DBG_CH_ALL, DBG_TRACE, ">>> %s\n", fn)
#  define DBG_LEAVE(fn)   DBG(DBG_CH_ALL, DBG_TRACE, "<<< %s\n", fn)
#  define DBG_LOG_INIT()  dbg_log_init(DBG_LOG_PATH)
#  define DBG_LOG_CLOSE() dbg_log_close()
# else
#  define DBG(ch, lvl, ...) ((void)0)
#  define DBG_ENTER(fn)     ((void)0)
#  define DBG_LEAVE(fn)     ((void)0)
#  define DBG_LOG_INIT()    ((void)0)
#  define DBG_LOG_CLOSE()   ((void)0)
# endif

/* --- Shorthand convenience macros --- */
# define DBG_ERR_MSG(ch, ...)   DBG((ch), DBG_ERR,   __VA_ARGS__)
# define DBG_WARN_MSG(ch, ...)  DBG((ch), DBG_WARN,  __VA_ARGS__)
# define DBG_INFO_MSG(ch, ...)  DBG((ch), DBG_INFO,  __VA_ARGS__)
# define DBG_TRACE_MSG(ch, ...) DBG((ch), DBG_TRACE, __VA_ARGS__)

/* --- Forward declarations for math types --- */
struct s_vec2;
struct s_vec3;
struct s_mat4;
struct s_transform;
struct s_aabb;

typedef struct s_vec2       t_vec2;
typedef struct s_vec3       t_vec3;
typedef struct s_mat4       t_mat4;
typedef struct s_transform  t_transform;
typedef struct s_aabb       t_aabb;

/* --- Maths print functions (srcs/debug/print/maths.c) --- */
void	print_vec2(t_vec2 *v);
void	print_vec3(t_vec3 *v);
void	print_mat4(t_mat4 *m);
void	print_transform(t_transform *t);
void	print_aabb(t_aabb *b);

#endif