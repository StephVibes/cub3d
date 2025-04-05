/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:52:33 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 16:28:29 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	print_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("texture[%d] = %s\n", i, map->textures[i]);
		i++;
	}
}

static void	print_floor_ceiling_colors(t_map *map)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("floor_color[%d]: %d\n", i, map->floor_color_rgb[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		printf("ceiling_color[%d]: %d\n", i, map->ceiling_color_rgb[i]);
		i++;
	}
}

static void	print_map_layout(t_map *map)
{
	int	i;

	i = 0;
	while (map->layout[i])
	{
		printf("[%d] = %s", i, map->layout[i]);
		i++;
	}
}

void	print_debug(t_map *map)
{
	print_textures(map);
	print_floor_ceiling_colors(map);
	printf("map height = %d\n", map->height);
	printf("map_width = %d\n", map->width);
	print_map_layout(map);
}
