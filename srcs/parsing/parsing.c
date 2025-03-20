#include "cub3d.h"

int	get_texture_index(char *line)
{
	int	j;
	char	*coord[4];

	coord[0] = "NO";
	coord[1] = "SO";
	coord[2] = "WE";
	coord[3] = "EA";
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
	int	color_set[2];
	i = 0;
	color_set[0] = 0;
	color_set[1] = 0;
	while (lines[i])
	{
		line = lines[i];
		if (line[0] == 'F')
		{
			floor_color = ft_split(line + 2, ',');
			j = 0;
			while (floor_color[j])
			{
				if (validate_color(floor_color[j], map, j, 0))
					error("Invalid color floor");
				j++;
			}
			if (j == 3)
				color_set[0] = 1;
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
			if (j == 3)
				color_set[1] = 1;
			ft_free_split(ceiling_color);
		}
		i++;
	}
	i = 0;
	while(i < 2)
	{
		if (color_set[i++] == 0)
			error("Color incomplete");

	}
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
//	printf("***map start = %d\n", i);
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
	if (map->map_height < 3 || map->map_width < 3)
		error("Map is too small");
	i = 0;
	map->layout = malloc(sizeof(char *) * (map->height + 1));
	while (lines[map_start + i])
	{
		map->layout[i] = ft_strdup(lines[map_start + i]);
		i++;
	}
	map->layout[map->height] = NULL;
}

#include <stdio.h>
#include <stdlib.h>

#define WALL '1'
#define EMPTY '0'

// Helper function to check if a cell is a player (N, S, W, or E)
int is_player(char c) {
    return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

// Recursive flood fill to check if an open space reaches the map boundary
int flood_fill(char **map, int **visited, int rows, int cols, int x, int y) {
    // If we reach the edge of the map, it's open
    if (x < 0 || y < 0 || x >= rows || y >= cols)
        return 1;
    
    // If it's a wall or already visited, stop
    if (map[x][y] == WALL || visited[x][y])
        return 0;

    // Mark the cell as visited
    visited[x][y] = 1;

    // Check all 4 directions
    return flood_fill(map, visited, rows, cols, x + 1, y) ||
           flood_fill(map, visited, rows, cols, x - 1, y) ||
           flood_fill(map, visited, rows, cols, x, y + 1) ||
           flood_fill(map, visited, rows, cols, x, y - 1);
}

// Function to check if the map is fully enclosed
int is_map_closed(char **map, int rows, int cols) {
    // Allocate a visited array
    int **visited = (int **)malloc(rows * sizeof(int *));
    if (!visited)
        return -1; // Memory allocation failure

    int i = 0;
    while (i < rows) {
        visited[i] = (int *)calloc(cols, sizeof(int));
        if (!visited[i]) {
            while (--i >= 0) // Free already allocated rows if allocation fails
                free(visited[i]);
            free(visited);
            return -1;
        }
        i++;
    }

    i = 0;
    int j, result = 1; // Assume the map is closed

    while (i < rows) {
        j = 0;
        while (j < cols) {
            if (map[i][j] == EMPTY || is_player(map[i][j])) {
                if (flood_fill(map, visited, rows, cols, i, j)) {
                    result = 0; // Found an open path to the outside
                    break;
                }
            }
            j++;
        }
        if (!result) break;
        i++;
    }

    // Free allocated memory
    i = 0;
    while (i < rows) {
        free(visited[i]);
        i++;
    }
    free(visited);

    return result;
}


void	validate_map(char **layout, t_map *map)
{
	int	i;
	int	j;
	int	player_set;

	i = 0;
	player_set = 0;
	while (layout[i])
	{
		j = 0;
		while (layout[i][j] != '\n')
		{
			if (!is_map_closed(layout, map->map_height, map->map_width))
				error("Map needs to be enclosed by walls");
			if (!(layout[i][j] == '0' || layout[i][j] == '1' || layout[i][j] == ' ' 
				|| layout[i][j] == 'N' || layout[i][j] == 'S' || layout[i][j] == 'E' || layout[i][j] == 'W'))
				error("Wrong value in the map");
			if ((layout[i][j] == 'N' || layout[i][j] == 'S' 
				|| layout[i][j] == 'E' || layout[i][j] == 'W') && player_set == 0)
			{
				player_set = 1;
				if (i == 0 || i == map->map_height - 1 || j == 0 || j == map->map_width - 1)
					error("Player on the edge");
			}
			else if ((layout[i][j] == 'N' || layout[i][j] == 'S'
				|| layout[i][j] == 'E' || layout[i][j] == 'W') && player_set == 1)
				error("More than one player");
			j++;
		}
		i++;
	}
	if (player_set == 0)
		error("No player found in the map");
}

void	parse_map(char **lines, t_map *map)
{
	int	map_start;

	map_start = find_map_start(lines);
	if (map_start > 0)
		get_map_info(lines, map, map_start);
	else
		error("map not found");
	validate_map(map->layout, map);
}
