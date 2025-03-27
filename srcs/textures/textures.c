#include "cub3d.h"

void    determine_text(int hp_x, int hp_y, t_maze *maze, int coord)
{
	double	mod; // Value 
	double	val;

	if (coord == 1 || coord == 2)
		mod = (hp_x - maze->map->offset_2dx) % maze->map->block;
	else
		mod = (hp_y - maze->map->offset_2dy) % maze->map->block;
	val = reescale(mod, maze->map->block);
	//con val buscar valor de txt_x
}

double	reescale(int value, int block) {
	double	new;

	new = value / (block - value);

	return (new);
}