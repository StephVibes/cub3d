#include "cub3d.h"

static int	count_lines(const char *file_name)
{
	int	fd;
	char	*line;
	int	num_lines;

	num_lines = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error("error opening the map"); // improve
	line = get_next_line(fd);
	while (line != NULL)
	{
		num_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return(num_lines);
}

char	**read_file(const char *file_name)
{
	int	num_lines;
	int	fd;
	char	**lines;
	int	i;
	char	*ext;

	i = 0;
	num_lines = count_lines(file_name);
	lines = malloc((num_lines + 1) * sizeof(char *));
	ext = ft_strrchr(file_name, '.');
	if (!ext)
		error("Missing map file extension");
	if (ft_strncmp(ext, ".cub", 4))
		error("Invalid map file extension");
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error("error opening the file"); // improve
	while(i < num_lines)
	{
		lines[i] = get_next_line(fd);
		//printf("%d == %s", i, lines[i]);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return(lines);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/* void	print_debug(t_map *map)
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
		printf("floor_color[%d]: %d\n", i, map->floor_color[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		printf("ceiling_color[%d]: %d\n", i, map->ceiling_color[i]);
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
} */

void wall_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while(map->layout[i] && i < map->height)
	{
		j = 0;
		while(map->layout[i][j] && j < map->width)
		{
			if(map->layout[i][j] == '1')
			{
				//edge cases
				//i= 0 and j = 0
				//i = W and j = H
				//i = 0 and j = H
				//i = w and j = 0
				if (i == map->height - 1)
				{
					if(map->layout[i-1][j] == '0' || map->layout[i-1][j] == 'N')
						map->layout[i][j] = 'x';
				}
				if(j> 0 && i> 0 && i < map->height - 1)
				{
					//x_wall
					if(map->layout[i+1][j] == '0' || map->layout[i-1][j] == '0')
						map->layout[i][j] = 'x';
					//y_wall
					if(map->layout[i][j+1] == '0' || map->layout[i][j-1] == '0')
						map->layout[i][j] = 'y';
					//column
				}
				else if(j == 0 && i != 0 && i < map->height - 1)
				{
					if(map->layout[i+1][j] == '0' || map->layout[i-1][j] == '0')
						map->layout[i][j] = 'x';
					if(map->layout[i][j+1] == '0' || map->layout[i][j+1] == 'N')
						map->layout[i][j] = 'y';
				}
				else if(j != 0 && i == 0 && i < map->height - 1) 
				{
					if(map->layout[i+1][j] == '0')
						map->layout[i][j] = 'x';
					if(map->layout[i][j+1] == '0' || map->layout[i][j-1] == '0')
						map->layout[i][j] = 'y';
				}
			}
			j++;
			//The 4 points rounding a point are:
			//map->layout[i-1][j]
			//map->layout[i+1][j]
			//map->layout[i][j-1]
			//map->layout[i][j+1]
		}
		i++;
	}
}

t_map	*load_map(const char *file_name)
{
	char	**lines;
	t_map	*map;
	
	lines = read_file(file_name);
	if (!lines)
        	return (NULL);

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	ft_memset(map, 0, sizeof(t_map)); // Initialize map to zero
	parse_textures(lines, map);
	parse_colors(lines, map);
	parse_map(lines, map);
	//wall_map(map);
	//print_debug(map);
	//validate_map(map);
	ft_free_split(lines); // Free the file lines
	return (map);
}
