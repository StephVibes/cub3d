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


void move_player_rotate(t_player *player)
{
	if (player->right_rotate)
		player->angle += ANGLE_SPEED;
	if (player->left_rotate)
		player->angle -= ANGLE_SPEED;
	if (player->angle > 2 * M_PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * M_PI;
}

void move_player_bf(t_player *player, double cos_angle, double sin_angle, double speed)
{
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

void	move_player(t_player *player)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move_player_rotate(player);
	move_player_bf(player, cos_angle, sin_angle, SPEED);
}

void	move_player_minimap(t_player *player, int block_map)
{
	double	speed;
	double	cos_angle;
	double	sin_angle;
	
	speed = SPEED * ((double)block_map / BLOCK);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move_player_rotate(player);
	move_player_bf(player, cos_angle, sin_angle, speed);
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
