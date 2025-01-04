#include "cub3d.h"

static void	events_init(t_maze *maze)
{
	mlx_hook(maze->win_ptr,
		DestroyNotify,
		StructureNotifyMask,
		close_handler,
		maze);
}

void	maze_init(t_maze *maze)
{
	maze -> mlx_ptr = mlx_init(); // connect with the minilibx
	if (maze -> mlx_ptr == NULL)
		error(); // improve
	maze -> win_ptr = mlx_new_window(maze -> mlx_ptr, WIDTH, HEIGHT, "Cub3D"); // create new window
	if (maze -> win_ptr == NULL)
	{
		mlx_destroy_display(maze -> mlx_ptr);
		free(maze -> mlx_ptr);
		error(); // improve
	}
	maze -> screen.img_ptr = mlx_new_image(maze -> mlx_ptr, WIDTH, HEIGHT); // create image
	if (maze -> screen.img_ptr == NULL)
	{
		mlx_destroy_window(maze -> mlx_ptr, maze -> win_ptr);
		mlx_destroy_display(maze -> mlx_ptr);
		free(maze -> mlx_ptr);
		error(); // improve
	}
	maze -> screen.data = mlx_get_data_addr(maze -> screen.img_ptr, &maze -> screen.bpp, &maze -> screen.line_length, &maze -> screen.endian);
	events_init(maze);
	//data_init()?
}
