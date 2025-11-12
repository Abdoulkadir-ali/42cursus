#include "map.h"

t_map_manager	init_map_manager(void)
{
	t_map_manager	m;

	m.maps = NULL;
	m.map_files = NULL;
	m.count = 0;
	m.current_index = 0;
	return (m);
}

t_map	*init_map(char *filename)
{
	t_map	*map;

	map = load_map(filename);
	if (map)
		apply_map_style(map);
	return (map);
}