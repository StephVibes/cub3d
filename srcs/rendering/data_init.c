/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:05:42 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:20:38 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_dimensions(t_maze *maze)
{
	maze->img_3d.width = WIDTH;
	maze->img_3d.height = HEIGHT;
	maze->img_2d.width = MAP_SIZE;
	maze->img_2d.height = MAP_SIZE;
}

static void	calculate_map_parameters(t_maze *maze)
{
	if (maze->map->width > maze->map->height)
		maze->map->block = MAP_SIZE / maze->map->width;
	else
		maze->map->block = MAP_SIZE / maze->map->height;
	maze->map->offset_2dx = (maze->img_2d.width - (maze->map->width
				* maze->map->block)) / 2;
	maze->map->offset_2dy = (maze->img_2d.height - (maze->map->height
				* maze->map->block)) / 2;
}

static void	init_player_positions(t_maze *maze)
{
	get_player_init_pos(maze);
	get_player_init_pos_minimap(maze);
	get_player_angle(maze);
	maze->player.ray_x = maze->player.x;
	maze->player.ray_y = maze->player.y;
	maze->map->mini_player.ray_y = maze->map->mini_player.y;
	maze->map->mini_player.ray_x = maze->map->mini_player.x;
}

void	init_textures(t_map *map)
{
	int	i;
	int	j;

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
				if (map->txt_imgs[j])
				{
					free(map->txt_imgs[j]);
					map->txt_imgs[j] = NULL;
				}
				j++;
			}
			return ;
		}
		i++;
	}
}

void	data_init(t_maze *maze)
{
	int	i;

	i = 0;
	maze->show_minimap = 0;
	while (i < 4)
	{
		maze->player.key_state[i] = 0;
		maze->map->mini_player.key_state[i] = 0;
		i++;
	}
	maze->player.right_rotate = 0;
	maze->player.left_rotate = 0;
	maze->player.angle = (3 * M_PI) / 2;
	maze->map->mini_player.right_rotate = 0;
	maze->map->mini_player.left_rotate = 0;
	maze->map->mini_player.angle = (3 * M_PI) / 2;
	init_dimensions(maze);
	calculate_map_parameters(maze);
	init_player_positions(maze);
	init_textures(maze->map);
	get_images_xpm(maze->map, maze);
}
