#include "cub3d.h"

void	my_pixel_put(int x, int y, t_image *img, int color)
{
	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return;
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->data + offset) = color;
}

void	draw_square(int x, int y, int size, int color, t_image *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_pixel_put(x + i, y + j, img, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_maze *maze)
{
/*	for (int y = 0; y < MAP_SIZE; y++)
    		for (int x = 0; x < MAP_SIZE; x++)
        		my_pixel_put(x, y, &maze->img_2d, 0x00FF00);
*/	char	**map;
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
				draw_square(x * SQUARE, y * SQUARE, SQUARE, color, &maze->img_2d);
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
	
	if (x < 0 || y < 0 || x >= maze->map->map_width || y >= maze->map->map_height)
		return (1);
	if (maze->map->layout[y][x] == '1')
		return (1);
	return (0);
}
