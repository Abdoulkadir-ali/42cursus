/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:46:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELS_H
# define CHANNELS_H

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

#endif
