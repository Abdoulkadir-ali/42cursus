/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:46:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

# include <stdarg.h>

/* --- Core log functions (srcs/debug/log.c) --- */
void	dbg_print(int ch, int lvl, const char *fmt, ...);
void	dbg_log_init(const char *path);
void	dbg_log_close(void);

#endif
