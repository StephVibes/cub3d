/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:37:38 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:41:42 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_maze *maze, t_ray *ray, double orig_y)
{
	double	ceiling;

	ceiling = 0;
	while (ceiling < orig_y)
	{
		my_pixel_put(ray->ray_id, (int)ceiling, &maze->img_3d,
			maze->map->ceiling_color);
		ceiling++;
	}
}

void	draw_floor(t_maze *maze, t_ray *ray, double floor)
{
	while (floor < HEIGHT)
	{
		my_pixel_put(ray->ray_id, (int)floor, &maze->img_3d,
			maze->map->floor_color);
		floor++;
	}
}

void	draw_line(t_maze *maze, t_ray *ray, double orig_y, double yy)
{
	double	y;
	int		color;
	int		tex_y;
	t_image	*txt_img;

	txt_img = maze->map->txt_imgs[ray->coord];
	y = orig_y;
	while (y < yy)
	{
		if (ray->coord != -1)
		{
			tex_y = (y - orig_y) / ray->factor_y;
			color = *(unsigned int *)(txt_img->data + txt_img->line_len * tex_y
					+ (int)ray->txt_x * (txt_img->bpp / 8));
			my_pixel_put(ray->ray_id, (int)y, &maze->img_3d, color);
		}
		y++;
	}
}

void	draw_utils(t_ray *ray, t_maze *maze)
{
	double	yy;
	double	orig_y;

	orig_y = (HEIGHT - ray->h) / 2;
	yy = ray->h + orig_y;
	draw_ceiling(maze, ray, orig_y);
	draw_floor(maze, ray, yy);
	draw_line(maze, ray, orig_y, yy);
}

void	draw_wall(t_maze *maze, int i, double ray_angle)
{
	ray_data(maze, i, ray_angle, &maze->player);
	hit_compass(&maze->ray[i], maze);
	def_coord(&maze->ray[i], maze);
	determine_text(&maze->ray[i], maze);
	draw_utils(&maze->ray[i], maze);
}
