#include "cub3d.h"

static void	data_init(t_maze *maze)
{
	maze->player.key_state[0] = 0;
	maze->player.key_state[1] = 0;
	maze->player.key_state[2] = 0;
	maze->player.key_state[3] = 0;
	maze->map->player_x = WIDTH / 2; //SACAR DEL MAPA
	maze->map->player_y = HEIGHT / 2; //SACAR DEL MAPA
	maze->player.x = maze->map->player_x; //decidir si actualizar o no
	maze->player.y = maze->map->player_y;
}

static void	events_init(t_maze *maze)
{
	mlx_hook(maze->win_ptr,
		KeyPress,
		KeyPressMask,
		key_press_handler,
		maze);
	mlx_hook(maze->win_ptr,
		KeyRelease,
		KeyReleaseMask,
		key_release_handler,
		maze);
	/*mlx_hook(maze->win_ptr,
		ButtonPress,
		ButtonPressMask,
		mouse_handler,
		maze);*/
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
		error("error initiliazing the minilibx"); // improve
	maze -> win_ptr = mlx_new_window(maze -> mlx_ptr, WIDTH, HEIGHT, "Cub3D"); // create new window
	if (maze -> win_ptr == NULL)
	{
		mlx_destroy_display(maze -> mlx_ptr);
		free(maze -> mlx_ptr);
		error("error creating the window with the minilibx"); // improve
	}
	maze -> screen.img_ptr = mlx_new_image(maze -> mlx_ptr, WIDTH, HEIGHT); // create image
	if (maze -> screen.img_ptr == NULL)
	{
		mlx_destroy_window(maze -> mlx_ptr, maze -> win_ptr);
		mlx_destroy_display(maze -> mlx_ptr);
		free(maze -> mlx_ptr);
		error("error creating the image with minilibx"); // improve
	}
	maze -> screen.data = mlx_get_data_addr(maze -> screen.img_ptr, &maze -> screen.bpp, &maze -> screen.line_len, &maze -> screen.endian);
	data_init(maze);
	//mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->screen.img_ptr, 0, 0);
	events_init(maze);
}