#include "cub3d.h"

void	draw_map(t_maze *maze)
{
	char	**map;
	int 	color;
	int		y;
	int		x;
	
	map = maze->map->layout;
	color = 0x000000FF;
	y = 0;
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * 35, y * 35, 35, color, &maze->screen);
			x++;
		}
		y++;
	}
}