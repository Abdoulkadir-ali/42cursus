/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"
#include "debug.h"
#include "parser.h"

/*
** Resolves relative texture path based on MTL file location.
** Returns allocated full path.
*/
static char	*resolve_path(const char *mtl_path, const char *tex_filename)
{
	char	*dir;
	char	*full_path;

	dir = path_get_dir(mtl_path);
	if (!dir)
		return (ft_strdup(tex_filename));
	full_path = ft_strjoin(dir, tex_filename);
	free(dir);
	return (full_path);
}

static void	parse_mtl_line(t_scene *scene, char *line, int *cur_mat,
		const char *mtl_path)
{
	char	*p;
	char	*arg;
	char	*tex_path;

	p = line;
	while (*p && (*p == ' ' || *p == '\t'))
		p++;
	if (!*p || *p == '#')
		return ;
	if (ft_strncmp(p, "newmtl", 6) == 0 && (p[6] == ' ' || p[6] == '\t'))
	{
		p += 6;
		while (*p && (*p == ' ' || *p == '\t'))
			p++;
		/* Trim trailing newline/space handled by parser_get_line usually removes \n */
		/* But we need to trim right space */
		arg = p;
		while (*arg && *arg != '\n' && *arg != '\r') arg++;
		*arg = 0;
		*cur_mat = scene_add_named_material(scene, p);
	}
	else if (ft_strncmp(p, "map_Kd", 6) == 0 && (p[6] == ' ' || p[6] == '\t')
			&& *cur_mat >= 0)
	{
		p += 6;
		while (*p && (*p == ' ' || *p == '\t'))
			p++;
		arg = p;
		while (*arg && *arg != '\n' && *arg != '\r') arg++;
		*arg = 0;
		tex_path = resolve_path(mtl_path, p);
		if (load_texture_xpm(scene, &scene->materials[*cur_mat].albedo_map,
				tex_path))
			printf("DEBUG: Loaded texture for material %s\n",
				scene->materials[*cur_mat].name);
		free(tex_path);
	}
}

/*
** Parses an MTL file and adds materials to the scene.
** Optimized version using t_parser.
*/
bool	parse_mtl(t_scene *scene, const char *path)
{
	t_parser	parser;
	int			fd;
	char		line[2048];
	int			cur_mat;

	printf("DEBUG: Parsing MTL file: %s\n", path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Could not open MTL file %s\n", path);
		return (false);
	}
	parser_init(&parser, fd);
	cur_mat = -1;
	while (parser_get_line(&parser, line, sizeof(line)))
	{
		parse_mtl_line(scene, line, &cur_mat, path);
	}
	close(fd);
	return (true);
}
