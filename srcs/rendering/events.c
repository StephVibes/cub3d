#include "cub3d.h"

int	close_handler(t_maze *maze)
{
	int	i;

	i = 0;
	mlx_destroy_image(maze->mlx_ptr, maze->img_3d.img_ptr);
	mlx_destroy_image(maze->mlx_ptr, maze->img_2d.img_ptr);
	while (i < 4)
	{
		free_xpm(maze->map->txt_imgs[i], maze);
		maze->map->txt_imgs[i] = NULL;
		i++;
	}
	mlx_destroy_window(maze->mlx_ptr, maze->win_ptr);
	mlx_destroy_display(maze->mlx_ptr);
	free(maze->mlx_ptr);
	exit(0); // TODO improve
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
	if (keycode == XK_Right)
		maze->player.right_rotate = 1;
	if (keycode == XK_Left)
		maze->player.left_rotate = 1;
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
	if (keycode == XK_Right)
		maze->player.right_rotate = 0;
	if (keycode == XK_Left)
		maze->player.left_rotate = 0;
	return (0);
}
