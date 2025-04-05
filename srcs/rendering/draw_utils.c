#include "cub3d.h"

int	touch_minimap(double px, double py, t_maze *maze)
{
	int	x;
	int	y;

	x = (px - maze->map->offset_2dx) / maze->map->block;
	y = (py - maze->map->offset_2dy) / maze->map->block;
	if (x < 0 || y < 0 || x >= maze->map->width || y >= maze->map->height)
		return (1);
	if (maze->map->layout[y][x] == '1')
		return (1);
	if (maze->map->layout[y][x] == 'x')
		return (2);
	if (maze->map->layout[y][x] == 'y')
		return (3);
	return (0);
}

int	touch(double px, double py, t_maze *maze)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (x < 0 || y < 0 || x >= maze->map->width || y >= maze->map->height)
		return (1);
	if (maze->map->layout[y][x] == '1')
		return (1);
	if (maze->map->layout[y][x] == 'x')
		return (2);
	if (maze->map->layout[y][x] == 'y')
		return (3);
	return (0);
}

void	clear_screen(t_image *screen)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			my_pixel_put(i, j, screen, COLOR_CREAM);
			j++;
		}
		i++;
	}
}
