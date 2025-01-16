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
				draw_square(x * SQUARE, y * SQUARE, SQUARE, color, &maze->screen);
			x++;
		}
		y++;
	}
}

int	touch(double px, double py, t_maze *maze)
{
	int	x;
	int	y;

	x = px / SQUARE;
	y = py / SQUARE;
	if (maze->map->layout[y][x] == '1')
		return (1);
	return (0);
}
