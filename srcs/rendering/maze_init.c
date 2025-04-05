/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:05:42 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:16:53 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	events_init(t_maze *maze)
{
	mlx_hook(maze->win_ptr, KeyPress, KeyPressMask, key_press_handler, maze);
	mlx_hook(maze->win_ptr, KeyRelease, KeyReleaseMask, key_release_handler,
		maze);
	mlx_hook(maze->win_ptr, DestroyNotify, StructureNotifyMask, close_handler,
		maze);
}

static void	init_mlx(t_maze *maze)
{
	maze->mlx_ptr = mlx_init();
	if (maze->mlx_ptr == NULL)
		error("error initiliazing the minilibx");
	maze->win_ptr = mlx_new_window(maze->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (maze->win_ptr == NULL)
	{
		mlx_destroy_display(maze->mlx_ptr);
		free(maze->mlx_ptr);
		error("error creating the window with the minilibx");
	}
}

static void	init_images(t_maze *maze)
{
	maze->img_3d.img_ptr = mlx_new_image(maze->mlx_ptr, WIDTH, HEIGHT);
	if (maze->img_3d.img_ptr == NULL)
	{
		mlx_destroy_window(maze->mlx_ptr, maze->win_ptr);
		mlx_destroy_display(maze->mlx_ptr);
		free(maze->mlx_ptr);
		error("error creating the image with minilibx");
	}
	maze->img_3d.data = mlx_get_data_addr(maze->img_3d.img_ptr,
			&maze->img_3d.bpp, &maze->img_3d.line_len, &maze->img_3d.endian);
	maze->img_2d.img_ptr = mlx_new_image(maze->mlx_ptr, MAP_SIZE, MAP_SIZE);
	if (maze->img_2d.img_ptr == NULL)
	{
		mlx_destroy_image(maze->mlx_ptr, maze->img_3d.img_ptr);
		mlx_destroy_window(maze->mlx_ptr, maze->win_ptr);
		mlx_destroy_display(maze->mlx_ptr);
		free(maze->mlx_ptr);
		error("error creating the image with minilibx");
	}
	maze->img_2d.data = mlx_get_data_addr(maze->img_2d.img_ptr,
			&maze->img_2d.bpp, &maze->img_2d.line_len, &maze->img_2d.endian);
}

void	maze_init(t_maze *maze)
{
	init_mlx(maze);
	init_images(maze);
	data_init(maze);
	events_init(maze);
}
