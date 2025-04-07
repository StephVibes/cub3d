/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:04:10 by alramire          #+#    #+#             */
/*   Updated: 2025/04/07 17:17:29 by alramire         ###   ########.fr       */
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
			error("It's not a digit");
			return (-1);
		}
		i++;
	}
	if (ft_atoi(color) < 0 || ft_atoi(color) > 255)
	{
		error("Number for RGB value is out of range, 0 < value < 255");
		return (-1);
	}
	if (type == 0)
		map->floor_color_rgb[index] = ft_atoi(color);
	else
		map->ceiling_color_rgb[index] = ft_atoi(color);
	return (0);
}

int	validate_color_array(char **color_array, t_map *map, int type)
{
	int	j;

	j = 0;
	while (color_array[j])
	{
		if (validate_color(color_array[j], map, j, type) == -1)
			return (-1);
		j++;
	}
	return (0);
}

int	check_color_format(char *line)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (line[i])
	{
		if (line[i] == ',')
			result++;
		i++;
	}
	if (result != 2)
		return (-1);
	return (0);
}
