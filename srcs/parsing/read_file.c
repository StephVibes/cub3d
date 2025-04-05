/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:05:27 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 16:05:48 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(const char *file_name)
{
	int		fd;
	char	*line;
	int		num_lines;

	num_lines = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error("error opening the map");
	line = get_next_line(fd);
	while (line != NULL)
	{
		num_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (num_lines);
}

char	**read_file(const char *file_name)
{
	int		num_lines;
	int		fd;
	char	**lines;
	int		i;
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
		error("error opening the file");
	while (i < num_lines)
	{
		lines[i] = get_next_line(fd);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
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
	char	**lines;
	t_map	*map;

	lines = read_file(file_name);
	if (!lines)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	ft_memset(map, 0, sizeof(t_map));
	parse_textures(lines, map);
	parse_colors(lines, map);
	rgb_to_int(map);
	parse_map(lines, map);
	ft_free_split(lines);
	return (map);
}
