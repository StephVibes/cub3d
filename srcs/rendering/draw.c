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
			if (x + i < MAP_SIZE && y + j < MAP_SIZE)
				my_pixel_put(x + i, y + j, img, color);
			j++;
		}
		i++;
	}
}

void	draw_map_cell(int x, int y, t_maze *maze)
{
	int	start_x;
	int	start_y;
	t_map	*map;

	map = maze->map;
	start_x = (maze->img_2d.width - (map->width * map->block)) / 2;
	start_y = (maze->img_2d.height - (map->height * map->block)) / 2;
    if (map->layout[y][x] == '1' || map->layout[y][x] == 'x' || map->layout[y][x] == 'y')
        draw_square(start_x + (x * map->block),
                    start_y + (y * map->block),
                    map->block, COLOR_BLACK, &maze->img_2d);
}

void	draw_map(t_maze *maze)
{
	int	y;
	int	x;

	y = 0;
	while (y < maze->map->height)
	{
		x = 0;
		while (x < maze->map->width)
		{
			draw_map_cell(x, y, maze);
			x++;
		}
		y++;
	}
}

void	draw_player(t_maze *maze)
{
	int	player_size;
	int	player_x;
	int	player_y;

	player_size = maze->map->block / 3;
	player_x = maze->map->mini_player.x - (player_size / 2);
	player_y = maze->map->mini_player.y - (player_size / 2);
	draw_square(player_x, player_y, player_size, COLOR_RED, &maze->img_2d);
}