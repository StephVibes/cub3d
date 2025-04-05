/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:30 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:45:06 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_loop(t_maze *maze)
{
	move_player(&maze->player);
	move_player_minimap(&maze->map->mini_player, maze->map->block);
	clear_screen(&maze->img_3d);
	draw_rays(maze, &maze->player);
	mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->img_3d.img_ptr,
		0, 0);
	if (maze->show_minimap)
	{
		clear_screen(&maze->img_2d);
		draw_rays_minimap(maze, &maze->map->mini_player);
		draw_map(maze);
		draw_player(maze);
		mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr,
			maze->img_2d.img_ptr, 40, HEIGHT - MAP_SIZE - 80);
	}
	return (0);
}
