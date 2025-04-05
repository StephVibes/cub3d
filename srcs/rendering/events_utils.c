/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:41:22 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 17:59:31 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_maze *maze)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free_xpm(maze->map->txt_imgs[i], maze);
		maze->map->txt_imgs[i] = NULL;
		i++;
	}
}

static void	free_map_data(t_maze *maze)
{
	int	i;

	i = 0;
	while (maze->map->layout[i])
	{
		free(maze->map->layout[i]);
		i++;
	}
	free(maze->map->layout);
	i = 0;
	while (maze->map->textures[i])
	{
		free(maze->map->textures[i]);
		i++;
	}
}

int	close_handler(t_maze *maze)
{
	mlx_destroy_image(maze->mlx_ptr, maze->img_3d.img_ptr);
	mlx_destroy_image(maze->mlx_ptr, maze->img_2d.img_ptr);
	free_textures(maze);
	mlx_destroy_window(maze->mlx_ptr, maze->win_ptr);
	mlx_destroy_display(maze->mlx_ptr);
	free(maze->mlx_ptr);
	free_map_data(maze);
	free(maze->map);
	exit(0);
}
