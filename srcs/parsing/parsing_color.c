/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:04:10 by alramire          #+#    #+#             */
/*   Updated: 2025/04/07 17:20:09 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_color(char *line, t_map *map, int type)
{
	char	**color;
	int		result;
	int		i;

	result = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',' && !ft_isdigit(line[i + 1]))
		{
			error("Invalid color comma");
			return (-1);
		}
		i++;
	}
	color = ft_split(line + 2, ',');
	i = 0;
	result = validate_color_array(color, map, type);
	ft_free_split(color);
	return (result);
}

static int	check_and_process_color(char *line, t_map *map, int type,
		int *color_set)
{
	int	result;

	if (check_color_format(line) == -1)
	{
		error("Color wrong format");
		return (-1);
	}
	result = process_color(line, map, type);
	if (result == -1)
		return (result);
	*color_set = !result;
	return (0);
}

static int	validate_color_settings(int *color_set)
{
	if (color_set[0] == 0 || color_set[1] == 0)
	{
		error("Color incomplete");
		return (-1);
	}
	return (0);
}

int	parse_colors(char **lines, t_map *map)
{
	int	i;
	int	color_set[2];
	int	result;

	i = 0;
	color_set[0] = 0;
	color_set[1] = 0;
	while (lines[i])
	{
		if (lines[i][0] == 'F')
			result = check_and_process_color(lines[i], map, 0, &color_set[0]);
		else if (lines[i][0] == 'C')
			result = check_and_process_color(lines[i], map, 1, &color_set[1]);
		else
			result = 0;
		if (result == -1)
			return (result);
		i++;
	}
	return (validate_color_settings(color_set));
}
