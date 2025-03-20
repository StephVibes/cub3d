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

void draw_map_cell(int x, int y, t_maze *maze)
{
    int start_x;
    int start_y;
    int color;

    color = 0x000000FF;  // Wall color

    // Calculate offsets to center the map
    start_x = (maze->img_2d.width - (maze->map->width * maze->map->block)) / 2;
    start_y = (maze->img_2d.height - (maze->map->height * maze->map->block)) / 2;

    if (maze->map->layout[y][x] == '1')
        draw_square(start_x + (x * maze->map->block),
                    start_y + (y * maze->map->block),
                    maze->map->block, color, &maze->img_2d);
}

void draw_map(t_maze *maze)
{
    int y;
    int x;

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


int	touch(double px, double py, t_maze *maze)
{
	int	x;
	int	y;

	x = (px - maze->map->offset_2dx) / maze->map->block;
	y = (py - maze->map->offset_2dy) / maze->map->block;
	
	if (x < 0 || y < 0 || x >= maze->map->width || y >= maze->map->height)
		return (1);
	if (maze->map->layout[y][x] == '1')
		return (1);
	return (0);
}

void	move_player(t_player *player)
{
	int	speed;
	double	angle_speed;
	double	cos_angle;
	double	sin_angle;

	speed = SPEED;
	angle_speed = ANGLE_SPEED;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->angle > 2 * M_PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * M_PI;
	if (player->key_state[0])
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_state[1])
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_state[2])
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->key_state[3])
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
}

void	draw_player(t_maze *maze)
{
	int	player_size;
	int	player_x;
	int	player_y;

	player_size = maze->map->block / 3;
	player_x = maze->player.x - (player_size / 2);
	player_y = maze->player.y - (player_size / 2);
	draw_square(player_x, player_y, player_size, 0xFF0000, &maze->img_2d);
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
			my_pixel_put(i, j, screen, 0x00000000);
			j++;
		}
		i++;
	}
}
