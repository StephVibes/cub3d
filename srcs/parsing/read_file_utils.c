/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:05:27 by alramire          #+#    #+#             */
/*   Updated: 2025/04/07 17:39:30 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(const char *file_name)
{
	int		fd;
	char	*line;
	int		num_lines;

	num_lines = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		error("error opening the map");
		exit(1);
	}
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

void	validate_file_extension(const char *file_name, char **lines)
{
	char	*ext;

	ext = ft_strrchr(file_name, '.');
	if (!ext)
	{
		error("Missing map file extension");
		free(lines);
		exit(1);
	}
	if (ft_strncmp(ext, ".cub", 4))
	{
		error("Invalid map file extension");
		free(lines);
		exit(1);
	}
}

int	open_map_file(const char *file_name, char **lines)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		error("error opening the file");
		free(lines);
		exit(1);
	}
	return (fd);
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

void	free_map_resources(t_map *map, char **lines)
{
	int	i;

	if (lines)
		ft_free_split(lines);
	if (map)
	{
		i = 0;
		while (i < 4 && map->textures[i])
		{
			free(map->textures[i]);
			i++;
		}
		if (map->layout)
			ft_free_split(map->layout);
		free(map);
	}
}
