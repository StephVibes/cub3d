/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:05:27 by alramire          #+#    #+#             */
/*   Updated: 2025/04/07 13:56:38 by alramire         ###   ########.fr       */
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
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		error("error opening the file");
		free(lines);
		exit(1);
	}
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
	int		i;

	lines = read_file(file_name);
	if (!lines)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	ft_memset(map, 0, sizeof(t_map));
	//if parse fails
	if(parse_textures(lines, map)== -1)
	{
		ft_free_split(lines);
		i = 0;
		while (i < 4)
		{
			free(map->textures[i]);
			i++;
		}
		free(map);
		exit(1);
	}
	//if colors fail
	if(parse_colors(lines, map) == -1)
	{
		ft_free_split(lines);
		//ft_free_split(map->textures);
		i = 0;
		while (i < 4)
		{
			free(map->textures[i]);
			i++;
		}
		free(map);
		exit(1);
	}
	rgb_to_int(map);
	//if map fail
	if (parse_map(lines, map) == -1)
	{
		ft_free_split(lines);
		i = 0;
		while (i < 4)
		{
			free(map->textures[i]);
			i++;
		}
		free(map);
		//ft_free_split(map->textures);
		//ft_free_split(map->layout);
		//free(map);
		exit(1);
	}
	ft_free_split(lines);
	return (map);
}
