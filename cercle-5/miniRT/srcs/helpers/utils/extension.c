/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 22:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 22:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

const char	*get_file_extension(const char *path)
{
	const char	*dot;

	if (!path)
		return ("");
	dot = ft_strrchr(path, '.');
	if (!dot || dot == path)
		return ("");
	return (dot + 1);
}
