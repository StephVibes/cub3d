/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_dir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:23:17 by alramire          #+#    #+#             */
/*   Updated: 2025/04/08 19:31:24 by smanriqu         ###   ########.fr       */
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

int	check_strict_compass_match(t_ray *ray)
{
	int	wall_facing_north[4];
	int	wall_facing_south[4];
	int	wall_facing_east[4];
	int	wall_facing_west[4];

	init_compass_arrays(wall_facing_north, wall_facing_south, 
		wall_facing_east, wall_facing_west);
	if (array_equals(ray->compass, wall_facing_north))
		return (0);
	if (array_equals(ray->compass, wall_facing_south))
		return (1);
	if (array_equals(ray->compass, wall_facing_east))
		return (2);
	if (array_equals(ray->compass, wall_facing_west))
		return (3);
	return (-1);
}
