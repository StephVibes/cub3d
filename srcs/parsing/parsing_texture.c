/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:02 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 15:06:30 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_index(char *line)
{
	int		j;
	char	*coord[4];

	coord[0] = "NO";
	coord[1] = "SO";
	coord[2] = "EA";
	coord[3] = "WE";
	j = 0;
	while (j < 4)
	{
		if (line[0] == coord[j][0] && line[1] == coord[j][1])
			return (j);
		j++;
	}
	return (-1);
}

void	parse_textures(char **lines, t_map *map)
{
	int		i;
	int		index;
	char	*line;

	i = 0;
	while (lines[i])
	{
		line = lines[i];
		index = get_texture_index(line);
		if (index != -1)
		{
			if (!map->textures[index])
				map->textures[index] = ft_strdup(line + 3);
			else
				error("Duplicated texture");
		}
		i++;
	}
	validate_textures(map->textures);
}
/* 
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
		if (!(line[i] == '0' || line[i] == '1' || line[i] == ' ' ||
			line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E'))
			return 0;
		i++;
	}
	return (ft_strchr(line, '0') || ft_strchr(line, '1') ||
            ft_strchr(line, 'N') || ft_strchr(line, 'S') ||
            ft_strchr(line, 'W') || ft_strchr(line, 'E'));
}

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

void	get_map_info(char **lines, t_map *map, int map_start)
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
		error("Map is too small");
	i = 0;
	map->layout = malloc(sizeof(char *) * (map->height + 1));
	while (lines[map_start + i] && lines[map_start + i][0] != '\n')
	{
		map->layout[i] = ft_strdup(lines[map_start + i]);
		i++;
	}
	map->layout[i] = NULL;
}

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
}
 */