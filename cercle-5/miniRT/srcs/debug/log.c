/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static int	g_dbg_fd = -1;

static const char	*ch_name(int ch)
{
	if (ch & DBG_CH_RENDER)
		return ("RENDER");
	if (ch & DBG_CH_BVH)
		return ("BVH");
	if (ch & DBG_CH_PHYSICS)
		return ("PHYSICS");
	if (ch & DBG_CH_PARSER)
		return ("PARSER");
	if (ch & DBG_CH_EDITOR)
		return ("EDITOR");
	if (ch & DBG_CH_ANIM)
		return ("ANIM");
	if (ch & DBG_CH_TEXTURE)
		return ("TEXTURE");
	return ("MISC");
}

static const char	*lvl_name(int lvl)
{
	if (lvl == DBG_ERR)
		return ("ERR");
	if (lvl == DBG_WARN)
		return ("WARN");
	if (lvl == DBG_INFO)
		return ("INFO");
	return ("TRACE");
}

static void	write_both(const char *buf, int len)
{
	if (write(1, buf, len) < 0)
		return ;
	if (g_dbg_fd >= 0)
		(void)write(g_dbg_fd, buf, len);
}

void	dbg_log_init(const char *path)
{
	if (g_dbg_fd >= 0)
		close(g_dbg_fd);
	g_dbg_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	dbg_log_close(void)
{
	if (g_dbg_fd >= 0)
		close(g_dbg_fd);
	g_dbg_fd = -1;
}

void	dbg_print(int ch, int lvl, const char *fmt, ...)
{
	char	buf[512];
	char	pfx[64];
	va_list	ap;
	int		plen;
	int		blen;

	va_start(ap, fmt);
	blen = vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	plen = snprintf(pfx, sizeof(pfx), "[%s/%s] ",
			ch_name(ch), lvl_name(lvl));
	write_both(pfx, plen);
	write_both(buf, blen);
}
