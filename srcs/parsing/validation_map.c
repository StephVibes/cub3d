/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:15:25 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 15:24:27 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	accept_valid(char c)
{
	return (c == EMPTY || c == WALL || c == 'N' || c == 'S' ||
		c == 'E' || c == 'W' || c == ' ');
}

int	accept_coord(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int check_player_position(char **layout, t_map *map, int i, int j)
{
	(void) layout;
	if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
		error("Player on the edge");
	return (1);
}

static void check_valid_characters(char **layout)
{
	int i;
	int j;

	i = 0;
	while (layout[i])
	{
		j = 0;
		while (layout[i][j] != '\n')
		{
			if (!accept_valid(layout[i][j]))
				error("Wrong value in the map");
			j++;
		}
		i++;
	}
}

static int find_player(char **layout, t_map *map)
{
	int i;
	int j;
	int player_found;

	player_found = 0;
	i = 0;
	while (layout[i])
	{
		j = 0;
		while (layout[i][j] != '\n')
		{
			if (accept_coord(layout[i][j]))
			{
				if (player_found)
					error("More than one player in the map");
				player_found = check_player_position(layout, map, i, j);
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		error("No player found in the map");
	return (player_found);
}

void validate_map(char **layout, t_map *map)
{
	if (!is_map_closed(layout, map->height, map->width))
		error("Map needs to be enclosed by walls");
	check_valid_characters(layout);
	find_player(layout, map);
}
/* 
void	print_debug(t_map *map)
{
	int i = 0;
	while (i < 4)
	{
		printf("texture[%d] = %s\n", i, map->textures[i]);
		i++;
	}
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
	printf("map height = %d\n", map->height);
	printf("map_width = %d\n", map->width);
	i = 0;
	while(map->layout[i])
	{
		printf("[%d] = %s", i, map->layout[i]);
		i++;
	}
}

void	parse_map(char **lines, t_map *map)
{
	int	map_start;

	map_start = find_map_start(lines);
	if (map_start > 0)
	{
		get_map_info(lines, map, map_start);
	}
	else
		error("map not found");
	validate_map(map->layout, map);
	print_debug(map);
} */
