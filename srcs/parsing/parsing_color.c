/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:04:10 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 16:45:39 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_color(char *color, t_map *map, int index, int type)
{
	int	i;

	i = 0;
	while (color[i] && color[i] != 10)
	{
		if (!ft_isdigit(color[i]) && color[i] != 32 && color[i] != 9)
		{
			printf("It's not a digit: '%c'\n", color[i]);
			return (1);
		}
		i++;
	}
	if (ft_atoi(color) < 0 || ft_atoi(color) > 255)
	{
		printf("Number for RGB value is out of range, 0 < value < 255");
		return (1);
	}
	if (type == 0)
		map->floor_color_rgb[index] = ft_atoi(color);
	else
		map->ceiling_color_rgb[index] = ft_atoi(color);
	return (0);
}

static int	validate_color_array(char **color_array, t_map *map, int type)
{
	int	j;

	j = 0;
	while (color_array[j])
	{
		if (validate_color(color_array[j], map, j, type))
			return (1);
		j++;
	}
	return (j != 3);
}

static int	process_floor_color(char *line, t_map *map)
{
	char	**floor_color;
	int		result;

	result = 0;
	floor_color = ft_split(line + 2, ',');
	if (validate_color_array(floor_color, map, 0))
		result = 1;
	ft_free_split(floor_color);
	return (result);
}

static int	process_ceiling_color(char *line, t_map *map)
{
	char	**ceiling_color;
	int		result;

	result = 0;
	ceiling_color = ft_split(line + 2, ',');
	if (validate_color_array(ceiling_color, map, 1))
		result = 1;
	ft_free_split(ceiling_color);
	return (result);
}

void	parse_colors(char **lines, t_map *map)
{
	int	i;
	int	color_set[2];

	i = 0;
	color_set[0] = 0;
	color_set[1] = 0;
	while (lines[i])
	{
		if (lines[i][0] == 'F')
			color_set[0] = !process_floor_color(lines[i], map);
		else if (lines[i][0] == 'C')
			color_set[1] = !process_ceiling_color(lines[i], map);
		i++;
	}
	if (color_set[0] == 0 || color_set[1] == 0)
		error("Color incomplete");
}
