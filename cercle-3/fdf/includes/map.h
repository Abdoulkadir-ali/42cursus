#ifndef MAP_H
# define MAP_H

# include "vectors.h"

/* ========== POINT STRUCTURE ========== */
// Represents a 3D point with position and color
typedef struct s_point
{
	t_vec3	pos;
	int		color;
}	t_point;

/* ========== MAP STRUCTURE ========== */
// Contains the grid of 3D points with metadata
typedef struct s_map
{
	int		width;
	int		height;
	int		min_z;
	int		max_z;
	t_point	**points;
}	t_map;

/* ========== MAP FUNCTIONS ========== */
// Forward declaration
typedef struct s_data	t_data;

// Create and initialize test map
t_map	*create_test_grid(void);

// Load map from file
t_map	*load_map(char *filename);

// Free map memory
void	free_map(t_map *map);

// Map selection
void	init_map_list(t_data *data);
void	cycle_map(t_data *data);

#endif
