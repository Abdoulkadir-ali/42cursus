/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:46:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# include "channels.h"
# include "log.h"

/* --- Legacy print macro (kept for compatibility) --- */
# if DEBUG
#  define ft_print_debug(...) (printf(__VA_ARGS__), fflush(stdout))
# else
#  define ft_print_debug(...) ((void)0)
# endif

/* --- Main dispatch macro --- */
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

#endif
