#include "cub3d.h"

int	close_handler(t_maze *maze)
{
	mlx_destroy_image(maze->mlx_ptr, maze->screen.img_ptr);
	mlx_destroy_window(maze->mlx_ptr, maze->win_ptr);
	mlx_destroy_display(maze->mlx_ptr);
	free(maze->mlx_ptr);
	exit(0); // improve
}

int	key_press_handler(int keycode, t_maze *maze)
{
	if (keycode == XK_w)
		maze->player.key_state[0] = 1;
	if (keycode == XK_s)
		maze->player.key_state[1] = 1;
	if (keycode == XK_a)
		maze->player.key_state[2] = 1;
	if (keycode == XK_d)
		maze->player.key_state[3] = 1;
	if (keycode == XK_Escape)
		close_handler(maze);
	return (0);
}

int	key_release_handler(int keycode, t_maze *maze)
{
	if (keycode == XK_w)
		maze->player.key_state[0] = 0;
	if (keycode == XK_s)
		maze->player.key_state[1] = 0;
	if (keycode == XK_a)
		maze->player.key_state[2] = 0;
	if (keycode == XK_d)
		maze->player.key_state[3] = 0;
	return (0);
}