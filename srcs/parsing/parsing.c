#include "cub3d.h"

void	parse_textures(char **lines, t_map *map)
{
	int	i;
	char	*line;

	i = 0;
	line = 	NULL;
	while (lines[i])
	{
		line = lines[i];
		if (line[0] == 'N' && line[1] == 'O')
			map->textures[0] = ft_strdup(line + 3);
		else if (line[0] == 'S' && line[1] == 'O')
			map->textures[1] = ft_strdup(line + 3);
		else if (line[0] == 'W' && line[1] == 'E')
			map->textures[2] = ft_strdup(line + 3);
		else if (line[0] == 'E' && line[1] == 'A')
			map->textures[3] = ft_strdup(line + 3);
		i++;
	}
}

int	validate_color(char *color, t_map *map, int index, int type)
{
	int	i;

	i = 0;
	while (color[i] && color[i] != 10)
	{
		if (!ft_isdigit(color[i]))
		{
			printf("is not digit: %d\n", color[i]);
			return (1);
		}
		i++;
	}
	if (ft_atoi(color) < 0 || ft_atoi(color) > 255)
	{
		printf("num fuera de rango");
		return (1);
	}
	if (type == 0)
		map->floor_color[index] = ft_atoi(color);
	else
		map->ceiling_color[index] = ft_atoi(color);
	return (0);
}

void	parse_colors(char **lines, t_map *map)
{
	int	i;
	int	j;
	char	*line;
	char	**floor_color;
	char	**ceiling_color;

	i = 0;
	while (lines[i])
	{
		line = lines[i];
		if (line[0] == 'F')
		{
			floor_color = ft_split(line + 2, ',');
			j = 0;
			while (floor_color[j])
			{
				//printf("validating color:%s\n", floor_color[j]);
				if (validate_color(floor_color[j], map, j, 0))
					error("Invalid color floor");
				j++;
			}
			ft_free_split(floor_color);
		}
		else if (line[0] == 'C')
		{
			ceiling_color = ft_split(line + 2, ',');
			j = 0;
			while (ceiling_color[j])
			{
				if (validate_color(ceiling_color[j], map, j, 1))
					error("Invalid color ceiling");
				j++;
			}
			ft_free_split(ceiling_color);
		}
		i++;
	}
}


int	find_map_start(char **lines)
{
	int	i;
	char	*line;

	i = 0;
	line = NULL;
	while (lines[i])
	{
		//printf("line nro = %d\n", i);
		line = lines[i];
		if ((line[0] == '0' || line[0] == '1' || line[0] == ' ') 
				&& (line[1] == '0' || line[1] == '1' || line[1] == ' '))
			return (i);
	i++;
	}
	return (0);
}

void	get_map_info(char **lines, t_map *map, int map_start)
{
	int	i;
	int	line_len;

	i = map_start;
	map->map_height = 0;
	map->map_width = 0;
	while (lines[i] && lines[i][0] != '\n')
	{
		line_len = ft_strlen(lines[i]);
		if (lines[i][line_len - 1] == '\n')
			line_len--;
		if (line_len > map->map_width)
			map->map_width = line_len;
		map->map_height++;
		i++;
	}
	i = 0;
	map->layout = malloc(sizeof(char *) * (map->map_height + 1));
	while (lines[map_start + i])
	{
		map->layout[i] = ft_strdup(lines[map_start + i]);
		i++;
	}
	map->layout[map->map_height] = NULL;
}

/*int	validate_map(char **lines, int map_start)
{
	int	i;
	int	j;

	i = map_start;

	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if(line[i][j] == '0' || line[i][j] == '1' || line[i][j] == ' ' || 
				line[i][j] == 'N' || line[i][j] == 'S' || line[i][j] == 'E' line[i][j] == 'W')
				j++;
		}
	}
}*/

void	parse_map(char **lines, t_map *map)
{
	int	map_start;

	map_start = find_map_start(lines);
	if (map_start)
	{
		get_map_info(lines, map, map_start);
	}
	//validate_map
}
