/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:17:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 19:28:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

static void	process_line(char *line)
{
	t_object	*obj;

	if (!line || *line == '\0')
		return ;
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
	printf("\n--- Parsing: %s\n", line);
	obj = parse_line(line);
	if (!obj)
		printf("Error: failed to parse line: %s\n", line);
	else
	{
		print_object(obj);
		destroy_object(obj);
	}
}

bool	parse_file(const char *path)
{
	struct stat		st;
	DIR				*d;
	struct dirent	*ent;
	int				fd;
	char			*line;
	char			full[4096];

	if (stat(path, &st) == -1)
	{
		perror("stat");
		return (false);
	}
	if (S_ISDIR(st.st_mode))
	{
		d = opendir(path);
		if (!d)
		{
			perror("opendir");
			return (false);
		}
		while ((ent = readdir(d)))
		{
			if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
				continue ;
			snprintf(full, sizeof(full), "%s/%s", path, ent->d_name);
			parse_file(full);
		}
		closedir(d);
		return (true);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (false);
	}
	while ((line = get_next_line(fd)))
	{
		process_line(line);
		free(line);
	}
	close(fd);
	return (true);
}


// int	main(int argc, char **argv)
// {
// 	int	i;
// 	struct stat st;

// 	if (argc == 1)
// 	{
// 		/* Prefer parsing the project `maps/` dir when available */
// 		if (stat("maps", &st) == 0 && S_ISDIR(st.st_mode))
// 		{
// 			parse_file("maps");
// 			return (0);
// 		}
// 		parse_file("srcs/objects/parsing/input/test.rt");
// 		return (0);
// 	}
// 	i = 1;
// 	while (i < argc)
// 	{
// 		parse_file(argv[i]);
// 		i++;
// 	}
// 	return (0);
// }
