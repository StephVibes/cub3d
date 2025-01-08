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
	printf("num_lines: %d\n", num_lines);
	return(num_lines);
}

char	**read_file(const char *file_name)
{
	int	num_lines;
	int	fd;
	char	**lines;
	int	i;

	i = 0;
	num_lines = count_lines(file_name);
	lines = malloc(num_lines * sizeof(char *));

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error("error opening the file"); // improve
	while(i < num_lines)
	{
		lines[i] = get_next_line(fd);
		printf("line[%d]: %s\n", i, lines[i]);
		i++;
	}
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

t_map	*load_map(const char *file_name)
{
    char	**lines = read_file(file_name);
    if (!lines)
        return NULL;

    t_map *map = malloc(sizeof(t_map));
    ft_memset(map, 0, sizeof(t_map)); // Initialize map to zero

    parse_textures(lines, map);
	printf("texture[0]: %s\n", map->textures[0]);
	printf("texture[1]: %s\n", map->textures[1]);
	printf("texture[2]: %s\n", map->textures[2]);
	printf("texture[3]: %s\n", map->textures[3]);
    parse_colors(lines, map);
	printf("floor_color[0]: %d\n", map->floor_color[0]);
	printf("floor_color[1]: %d\n", map->floor_color[1]);
    //parse_map(lines, map);

    // validate_map(map);
    ft_free_split(lines); // Free the file lines
    return map;
}
