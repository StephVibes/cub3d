/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:23:17 by alramire          #+#    #+#             */
/*   Updated: 2025/04/08 19:29:54 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_vertical_ambiguity(t_ray *ray, t_ray *prev)
{
	if (ray->compass[0] == 1 && ray->compass[1] == 0
		&& ray->compass[2] == 1 && ray->compass[3] == 0)
	{
		if (prev->coord == 3)
			return (3);
		else
			return (1);
	}
	if (ray->compass[0] == 0 && ray->compass[1] == 1
		&& ray->compass[2] == 1 && ray->compass[3] == 0)
	{
		if (prev->coord == 0)
			return (0);
		else
			return (3);
	}
	return (-1);
}

static int	handle_horizontal_ambiguity(t_ray *ray, t_ray *prev)
{
	if (ray->compass[0] == 1 && ray->compass[1] == 0
		&& ray->compass[2] == 0 && ray->compass[3] == 1)
	{
		if (prev->coord == 1)
			return (1);
		else
			return (2);
	}
	if (ray->compass[0] == 0 && ray->compass[1] == 1
		&& ray->compass[2] == 0 && ray->compass[3] == 1)
	{
		if (prev->coord == 2)
			return (2);
		else
			return (0);
	}
	return (-1);
}

static int	check_ambiguous_compass_cases(t_ray *ray, t_maze *maze)
{
	t_ray	*prev;
	int		result;

	prev = &maze->ray[ray->ray_id - 1];
	result = handle_vertical_ambiguity(ray, prev);
	if (result != -1)
		return (result);
	result = handle_horizontal_ambiguity(ray, prev);
	if (result != -1)
		return (result);
	return (-1);
}

void	def_coord(t_ray *ray, t_maze *maze)
{
	int	coord;

	coord = check_strict_compass_match(ray);
	if (coord != -1)
	{
		ray->coord = coord;
		return ;
	}
	coord = check_ambiguous_compass_cases(ray, maze);
	if (coord != -1)
	{
		ray->coord = coord;
		return ;
	}
	ray->coord = maze->ray[ray->ray_id - 1].coord;
}

void	hit_compass(t_ray *ray, t_maze *maze)
{
	ray->compass[0] = touch(ray->hit_point.x, ray->hit_point.y - 1, maze);
	ray->compass[1] = touch(ray->hit_point.x, ray->hit_point.y + 1, maze);
	ray->compass[2] = touch(ray->hit_point.x + 1, ray->hit_point.y, maze);
	ray->compass[3] = touch(ray->hit_point.x - 1, ray->hit_point.y, maze);
}
