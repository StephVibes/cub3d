/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:15:25 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 16:36:55 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_player_position(char **layout, t_map *map, int i, int j)
{
	(void)layout;
	if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
		error("Player on the edge");
	return (1);
}

static void	check_valid_characters(char **layout)
{
	int	i;
	int	j;

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

static int	find_player(char **layout, t_map *map)
{
	int	i;
	int	j;
	int	player_found;

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

void	validate_map(char **layout, t_map *map)
{
	if (!is_map_closed(layout, map->height, map->width))
		error("Map needs to be enclosed by walls");
	check_valid_characters(layout);
	find_player(layout, map);
}
