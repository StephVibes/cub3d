/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:05:27 by alramire          #+#    #+#             */
/*   Updated: 2025/04/08 19:40:02 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_visited_array(int **visited, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	accept_valid(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

int	accept_coord(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	rgb_to_int(t_map *map)
{
	map->ceiling_color = (map->ceiling_color_rgb[0] << 16) | 
		(map->ceiling_color_rgb[1] << 8) | map->ceiling_color_rgb[2];
	map->floor_color = (map->floor_color_rgb[0] << 16) | 
		(map->floor_color_rgb[1] << 8) | map->floor_color_rgb[2];
}

int	is_map_line(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == ' '
				|| line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
				|| line[i] == 'E'))
			return (0);
		i++;
	}
	return (ft_strchr(line, '0') || ft_strchr(line, '1') || ft_strchr(line, 'N')
		|| ft_strchr(line, 'S') || ft_strchr(line, 'W') || ft_strchr(line,
			'E'));
}
