/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:30 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:23:02 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	while_touch(t_player *player, t_maze *maze, double ray_angle, int i)
{
	double	next_x;
	double	next_y;

	while (!(touch(player->ray_x, player->ray_y, maze)))
	{
		next_x = player->ray_x + cos(ray_angle);
		next_y = player->ray_y + sin(ray_angle);
		if (touch(next_x, player->ray_y, maze) && touch(player->ray_x, next_y,
				maze))
		{
			draw_wall(maze, i, ray_angle);
			break ;
		}
		player->ray_x = next_x;
		player->ray_y = next_y;
	}
	draw_wall(maze, i, ray_angle);
}

void	while_touch_minimap(t_player *player, t_maze *maze, double ray_angle)
{
	double	next_x;
	double	next_y;

	while (!(touch_minimap(player->ray_x, player->ray_y, maze)))
	{
		my_pixel_put((int)player->ray_x, (int)player->ray_y, &maze->img_2d,
			COLOR_GREEN_1);
		next_x = player->ray_x + cos(ray_angle);
		next_y = player->ray_y + sin(ray_angle);
		if (touch_minimap(next_x, player->ray_y, maze)
			&& touch_minimap(player->ray_x, next_y, maze))
		{
			break ;
		}
		player->ray_x = next_x;
		player->ray_y = next_y;
	}
}

void	draw_rays(t_maze *maze, t_player *player)
{
	double	angle_step;
	int		i;
	double	ray_angle;

	angle_step = FOV / (N_RAYS - 1);
	i = 0;
	while (i < WIDTH)
	{
		ray_angle = player->angle - (FOV / 2) + (i * angle_step);
		player->ray_x = player->x;
		player->ray_y = player->y;
		while_touch(player, maze, ray_angle, i);
		i++;
	}
}

void	draw_rays_minimap(t_maze *maze, t_player *player)
{
	double	angle_step;
	int		i;
	double	ray_angle;

	angle_step = FOV / (N_RAYS - 1);
	i = 0;
	while (i < WIDTH)
	{
		ray_angle = player->angle - (FOV / 2) + (i * angle_step);
		player->ray_x = player->x;
		player->ray_y = player->y;
		while_touch_minimap(player, maze, ray_angle);
		i++;
	}
}
