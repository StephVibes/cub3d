#include "cub3d.h"

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

void	calculate_map_dimensions(char **lines, t_map *map, int map_start)
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

void	get_map_info(char **lines, t_map *map, int map_start)
{
	calculate_map_dimensions(lines, map, map_start);
	allocate_map_layout(lines, map, map_start);
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
