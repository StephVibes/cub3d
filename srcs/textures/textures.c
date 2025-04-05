/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:44:34 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:44:52 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	reescale(int value, int block, int coord)
{
	double	new;

	if (block == 0)
		return (0.0);
	new = (double)value / (double)block;
	if (coord == 0 || coord == 2)
		return (1 - new);
	else
		return (new);
}

double	get_text_x(double val, int txt_width)
{
	double	text_x;

	if (val < 0.0)
		val = 0.0;
	if (val > 1.0)
		val = 1.0;
	text_x = floor(val * (txt_width - 1));
	return (text_x);
}

void	determine_text(t_ray *ray, t_maze *maze)
{
	double	mod;
	double	val_x;

	if (ray->coord == 0 || ray->coord == 1)
		mod = ((int)ray->hit_point.x) % BLOCK;
	else
		mod = ((int)ray->hit_point.y) % BLOCK;
	val_x = reescale(mod, BLOCK, ray->coord);
	ray->txt_x = get_text_x(val_x, maze->map->txt_imgs[ray->coord]->width);
	ray->factor_y = ray->h / maze->map->txt_imgs[ray->coord]->height;
}
