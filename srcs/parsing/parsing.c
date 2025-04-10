/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:20:25 by alramire          #+#    #+#             */
/*   Updated: 2025/04/08 19:43:51 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_map_start(char **lines)
{
	int	i;

	if (!lines)
		return (-1);
	i = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	calculate_map_dimensions(char **lines, t_map *map, int map_start)
{
	int	i;
	int	line_len;

	i = map_start;
	map->height = 0;
	map->width = 0;
	while (lines[i] && lines[i][0] != '\n')
	{
		line_len = ft_strlen(lines[i]);
		if (lines[i][line_len - 1] == '\n')
			line_len--;
		if (line_len > map->width)
			map->width = line_len;
		map->height++;
		i++;
	}
	if (map->height < 3 || map->width < 3)
	{
		error("Map is too small");
		return (-1);
	}
	return (0);
}

void	allocate_map_layout(char **lines, t_map *map, int map_start)
{
	int	i;

	i = 0;
	map->layout = malloc(sizeof(char *) * (map->height + 1));
	if (!map->layout)
		error("Memory allocation failed");
	while (lines[map_start + i] && lines[map_start + i][0] != '\n')
	{
		map->layout[i] = ft_strdup(lines[map_start + i]);
		if (!map->layout[i])
			error("Memory allocation failed");
		i++;
	}
	map->layout[i] = NULL;
}

int	get_map_info(char **lines, t_map *map, int map_start)
{
	if (calculate_map_dimensions(lines, map, map_start) == -1)
		return (-1);
	allocate_map_layout(lines, map, map_start);
	return (0);
}

int	parse_map(char **lines, t_map *map)
{
	int	map_start;

	map_start = find_map_start(lines);
	if (map_start > 0)
	{
		if (get_map_info(lines, map, map_start) == -1)
			return (-1);
	}
	else
	{
		error("map not found or not in the right position");
		return (-1);
	}
	if (validate_map(map->layout, map) == -1)
		return (-1);
	return (0);
}
