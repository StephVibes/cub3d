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

// void	parse_map(char **lines, t_map *map)
// {

// }
