/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:23:17 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:38:24 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	array_equals(int arr[], int expected[])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (arr[i] != expected[i])
			return (0);
		i++;
	}
	return (1);
}

void	init_compass_arrays(int north[4], 
		int south[4], int east[4], int west[4])
{
	north[0] = 0;
	north[1] = 1;
	north[2] = 1;
	north[3] = 1;
	south[0] = 1;
	south[1] = 0;
	south[2] = 1;
	south[3] = 1;
	east[0] = 1;
	east[1] = 1;
	east[2] = 0;
	east[3] = 1;
	west[0] = 1;
	west[1] = 1;
	west[2] = 1;
	west[3] = 0;
}

void	check_compass_direction(t_ray *ray, t_maze *maze)
{
	int	wall_facing_north[4];
	int	wall_facing_south[4];
	int	wall_facing_east[4];
	int	wall_facing_west[4];

	init_compass_arrays(wall_facing_north, wall_facing_south, 
		wall_facing_east, wall_facing_west);
	if (array_equals(ray->compass, wall_facing_north))
		ray->coord = 0;
	else if (array_equals(ray->compass, wall_facing_south))
		ray->coord = 1;
	else if (array_equals(ray->compass, wall_facing_east))
		ray->coord = 2;
	else if (array_equals(ray->compass, wall_facing_west))
		ray->coord = 3;
	else
		ray->coord = maze->ray[ray->ray_id - 1].coord;
}

void	def_coord(t_ray *ray, t_maze *maze)
{
	(void)maze;
	check_compass_direction(ray, maze);
}

void	hit_compass(t_ray *ray, t_maze *maze)
{
	ray->compass[0] = touch(ray->hit_point.x, ray->hit_point.y - 1, maze);
	ray->compass[1] = touch(ray->hit_point.x, ray->hit_point.y + 1, maze);
	ray->compass[2] = touch(ray->hit_point.x + 1, ray->hit_point.y, maze);
	ray->compass[3] = touch(ray->hit_point.x - 1, ray->hit_point.y, maze);
}
