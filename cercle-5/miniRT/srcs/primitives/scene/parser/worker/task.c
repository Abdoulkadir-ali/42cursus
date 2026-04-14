/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

void	cleanup_task(t_rt_line_task *t)
{
	free(t->lines);
	free(t->results);
	free(t->statuses);
	free(t->resources);
}

bool	prep_task(t_rt_line_task *t, char *content)
{
	t->lines = ft_split(content, '\n');
	free(content);
	if (!t->lines)
		return (false);
	t->count = 0;
	while (t->lines[t->count])
		t->count++;
	t->results = ft_calloc(t->count, sizeof(t_parse_obj));
	t->statuses = ft_calloc(t->count, sizeof(bool));
	t->resources = ft_calloc(t->count, sizeof(t_mesh_resource));
	return (t->results && t->statuses && t->resources);
}
