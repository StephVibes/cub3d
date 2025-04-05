/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:23:17 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:43:19 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	perp_wall_dst(t_player *player, double ray_angle)
{
	double	ray_length;
	double	correction_angle;
	double	ray_dir_x;
	double	ray_dir_y;

	ray_dir_x = player->ray_x - player->x;
	ray_dir_y = player->ray_y - player->y;
	ray_length = sqrt(ray_dir_x * ray_dir_x + ray_dir_y * ray_dir_y);
	correction_angle = ray_angle - player->angle;
	while (correction_angle > M_PI)
		correction_angle -= 2 * M_PI;
	while (correction_angle < -M_PI)
		correction_angle += 2 * M_PI;
	return (ray_length * cos(correction_angle));
}

double	get_wall_distance(t_player *player)
{
	double	dst;

	dst = sqrt((player->ray_y - player->y) * (player->ray_y - player->y)
			+ (player->ray_x - player->x) * (player->ray_x - player->x));
	return (dst);
}

double	dst_to_h(double dst)
{
	double	h;
	double	slope;

	slope = (MIN_WALL - HEIGHT) / (MAX_DST);
	h = slope * dst + HEIGHT;
	if (dst > MAX_DST)
		return (MIN_WALL);
	return (h);
}

void	ray_data(t_maze *maze, int i, double ray_angle, t_player *player)
{
	maze->ray[i].ray_id = i;
	maze->ray[i].coord = -1;
	maze->ray[i].hit_point.x = player->ray_x;
	maze->ray[i].hit_point.y = player->ray_y;
	maze->ray[i].angle = 0.0;
	maze->ray[i].angle = ray_angle;
	maze->ray[i].dst = perp_wall_dst(player, ray_angle);
	maze->ray[i].h = (BLOCK / maze->ray[i].dst) * (HEIGHT / 2);
}
