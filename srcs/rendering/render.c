#include "cub3d.h"

static void	my_pixel_put(int x, int y, t_image *screen, int color)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	int	offset;

	offset = (y * screen->line_len) + (x * (screen->bpp / 8));
	*(unsigned int *)(screen->data + offset) = color;
}

void	draw_square(int x, int y, int size, int color, t_image *screen)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_pixel_put(x + i, y + j, screen, color);
			j++;
		}
		i++;
	}
}

void	move_square(t_player *player)
{
	int	speed = 5;

	if (player->key_state[0])
		player->y -= speed;
	if (player->key_state[1])
		player->y += speed;
	if (player->key_state[2])
		player->x -= speed;
	if (player->key_state[3])
		player->x += speed;
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

int	draw_loop(t_maze *maze)
{
	move_square(&maze->player);
	clear_screen(&maze->screen);
	draw_square(maze->player.x, maze->player.y, 10, 0x00FF0000, &maze->screen);
	mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->screen.img_ptr, 0, 0);
	return (0);
}
