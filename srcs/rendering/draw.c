/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:50:32 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:04:56 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(int x, int y, t_image *img, int color)
{
	int	offset;

	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return ;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->data + offset) = color;
}

void	draw_square(t_point *p, int color, t_image *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->ray)
	{
		j = 0;
		while (j < p->ray)
		{
			if (p->x + i < MAP_SIZE && p->y + j < MAP_SIZE)
				my_pixel_put(p->x + i, p->y + j, img, color);
			j++;
		}
		i++;
	}
}

void	draw_map_cell(int x, int y, t_maze *maze)
{
	int		start_x;
	int		start_y;
	t_map	*map;
	t_point	p;

	map = maze->map;
	start_x = (maze->img_2d.width - (map->width * map->block)) / 2;
	start_y = (maze->img_2d.height - (map->height * map->block)) / 2;
	if (map->layout[y][x] == '1' || map->layout[y][x] == 'x'
		|| map->layout[y][x] == 'y')
	{
		p.x = start_x + (x * map->block);
		p.y = start_y + (y * map->block);
		p.ray = map->block;
		draw_square(&p, COLOR_BLACK, &maze->img_2d);
	}
}

void	draw_map(t_maze *maze)
{
	int	y;
	int	x;

	y = 0;
	while (y < maze->map->height)
	{
		x = 0;
		while (x < maze->map->width)
		{
			draw_map_cell(x, y, maze);
			x++;
		}
		y++;
	}
}

void	draw_player(t_maze *maze)
{
	t_point	player;

	player.ray = maze->map->block / 3;
	player.x = maze->map->mini_player.x - (player.ray / 2);
	player.y = maze->map->mini_player.y - (player.ray / 2);
	draw_square(&player, COLOR_RED, &maze->img_2d);
}
