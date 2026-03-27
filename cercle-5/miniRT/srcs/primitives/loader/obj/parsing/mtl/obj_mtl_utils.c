/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_mtl_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:30:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

void	obj_parse_mtllib_raw(t_obj_ctx *ctx, t_parser *p, t_raw_model *model,
		const char *obj_path)
{
	char	name[256];
	char	*dir;
	char	*full;
	int		i;

	(void)ctx;
	i = 0;
	parser_skip_spaces(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;
	dir = path_get_dir(obj_path);
	full = ft_strdup(name);
	if (dir)
	{
		free(full);
		full = ft_strjoin(dir, name);
		free(dir);
	}
	mtl_load(full, model);
	free(full);
}

void	obj_parse_usemtl_raw(t_obj_ctx *ctx, t_parser *p, t_raw_model *model)
{
	char	name[256];
	int		i;
	int		j;

	i = 0;
	parser_skip_spaces(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;
	ctx->current_mat_id = -1;
	j = 0;
	while (j < model->mat_count)
	{
		if (ft_strcmp(model->materials[j].name, name) == 0)
		{
			ctx->current_mat_id = j;
			break ;
		}
		j++;
	}
}

void	obj_parse_mtllib_to_scene(t_obj_ctx *ctx, t_parser *p, t_scene *scene,
		const char *obj_path)
{
	char    name[256];
	char    *dir;
	char    *full;
	int     i;
	int     base;

	(void)ctx;
	i = 0;
	parser_skip_spaces(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;
	dir = path_get_dir(obj_path);
	full = ft_strdup(name);
	if (dir)
	{
		free(full);
		full = ft_strjoin(dir, name);
		free(dir);
	}
	base = scene->mat_count;
	mtl_load_to_scene(full, scene);
	if (scene->mat_count > base)
		ctx->first_mtl_id = base;
	free(full);
}

void	obj_parse_usemtl_to_scene(t_obj_ctx *ctx, t_parser *p, t_scene *scene)
{
	char    name[256];
	int     i;

	i = 0;
	parser_skip_spaces(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;
	ctx->current_mat_id = -1;
	ctx->current_mat_id = scene_find_material(scene, name);
}
