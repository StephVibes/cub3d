/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:05:27 by alramire          #+#    #+#             */
/*   Updated: 2025/04/07 17:39:53 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	read_map_lines(int fd, char **lines, int num_lines)
{
	int	i;

	i = 0;
	while (i < num_lines)
	{
		lines[i] = get_next_line(fd);
		i++;
	}
	lines[i] = NULL;
	close(fd);
}

char	**read_file(const char *file_name)
{
	int		num_lines;
	int		fd;
	char	**lines;

	num_lines = count_lines(file_name);
	lines = malloc((num_lines + 1) * sizeof(char *));
	if (!lines)
		return (NULL);
	validate_file_extension(file_name, lines);
	fd = open_map_file(file_name, lines);
	read_map_lines(fd, lines, num_lines);
	return (lines);
}

static t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	ft_memset(map, 0, sizeof(t_map));
	return (map);
}

static int	parse_map_data(char **lines, t_map *map)
{
	if (parse_textures(lines, map) == -1)
		return (-1);
	if (parse_colors(lines, map) == -1)
		return (-1);
	rgb_to_int(map);
	if (parse_map(lines, map) == -1)
		return (-1);
	return (0);
}

t_map	*load_map(const char *file_name)
{
	char	**lines;
	t_map	*map;

	lines = read_file(file_name);
	if (!lines)
		return (NULL);
	map = init_map();
	if (!map)
	{
		ft_free_split(lines);
		return (NULL);
	}
	if (parse_map_data(lines, map) == -1)
	{
		free_map_resources(map, lines);
		exit(1);
	}
	ft_free_split(lines);
	return (map);
}
