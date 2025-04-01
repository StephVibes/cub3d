#include "cub3d.h"


static void	data_init(t_maze *maze)
{
	int	i;

	i = 0;
	maze->show_minimap = 0;
	while (i < 4)
	{
		maze->player.key_state[i++] = 0;
		maze->map->mini_player.key_state[i++] = 0;
	}
	maze->player.right_rotate = 0;
	maze->player.left_rotate = 0;
	maze->player.angle = (3 * M_PI) / 2; // depending on N S W E in map

	maze->map->mini_player.right_rotate = 0;
	maze->map->mini_player.left_rotate = 0;
	maze->map->mini_player.angle = (3 * M_PI) / 2; // depending on N S W E in map

	maze->img_3d.width = WIDTH;
	maze->img_3d.height = HEIGHT;
	maze->img_2d.width = MAP_SIZE;
	maze->img_2d.height = MAP_SIZE;
	if (maze->map->width > maze->map->height)
		maze->map->block= MAP_SIZE / maze->map->width;
	else
		maze->map->block = MAP_SIZE / maze->map->height;
	maze->map->offset_2dx = (maze->img_2d.width - (maze->map->width * maze->map->block)) / 2;
	maze->map->offset_2dy = (maze->img_2d.height - (maze->map->height * maze->map->block)) / 2;
	get_player_init_pos(maze);
	get_player_init_pos_minimap(maze);
	get_player_angle(maze);
	maze->player.ray_x = maze->player.x;
	maze->player.ray_y = maze->player.y;
	maze->map->mini_player.ray_y = maze->map->mini_player.y;
	maze->map->mini_player.ray_x = maze->map->mini_player.x;
	init_textures(maze->map);
	get_images_xpm(maze->map, maze);
}

void	init_textures(t_map *map)
{
	int i;
    int j;

    i = 0;
    j = 0;
    while (i < 4)
    {
        map->txt_imgs[i] = (t_image *)malloc(sizeof(t_image));
        if (map->txt_imgs[i] == NULL)
        {
            error("Memory allocation failed");
            while (j < i)
            {
                if(map->txt_imgs[j])
                {
                    free(map->txt_imgs[j]);
                    map->txt_imgs[j] = NULL;
                }
                j++;
            }
            return;
        }
		i++;
	}
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
		error("error initiliazing the minilibx"); // TODO improve
	maze -> win_ptr = mlx_new_window(maze -> mlx_ptr, WIDTH, HEIGHT, "Cub3D"); // create new window
	if (maze -> win_ptr == NULL)
	{
		mlx_destroy_display(maze -> mlx_ptr);
		free(maze -> mlx_ptr);
		error("error creating the window with the minilibx"); // TODO improve
	}
	maze -> img_3d.img_ptr = mlx_new_image(maze -> mlx_ptr, WIDTH, HEIGHT); // create 3d image
	if (maze -> img_3d.img_ptr == NULL)
	{
		mlx_destroy_window(maze -> mlx_ptr, maze -> win_ptr);
		mlx_destroy_display(maze -> mlx_ptr);
		free(maze -> mlx_ptr);
		error("error creating the image with minilibx"); // TODO improve
	}
	maze -> img_2d.img_ptr = mlx_new_image(maze -> mlx_ptr, MAP_SIZE, MAP_SIZE); // create 2d image
 	if (maze -> img_2d.img_ptr == NULL)
 	{
		mlx_destroy_window(maze -> mlx_ptr, maze -> win_ptr);
		mlx_destroy_display(maze -> mlx_ptr);
		free(maze -> mlx_ptr);
		error("error creating the image with minilibx"); // TODO improve
	}
	maze -> img_3d.data = mlx_get_data_addr(maze -> img_3d.img_ptr, &maze -> img_3d.bpp, 
			&maze -> img_3d.line_len, &maze -> img_3d.endian);
	maze -> img_2d.data = mlx_get_data_addr(maze -> img_2d.img_ptr, &maze -> img_2d.bpp,
			&maze -> img_2d.line_len, &maze -> img_2d.endian);
	data_init(maze);
	events_init(maze);
}
