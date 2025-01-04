#include "cub3d.h"

int	close_handler(t_maze *maze)
{
	mlx_destroy_image(maze->mlx_ptr, maze->screen.img_ptr);
	mlx_destroy_window(maze->mlx_ptr, maze->win_ptr);
	mlx_destroy_display(maze->mlx_ptr);
	free(maze->mlx_ptr);
	exit(0); // improve
}
