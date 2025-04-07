/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:02 by alramire          #+#    #+#             */
/*   Updated: 2025/04/07 17:40:14 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_index(char *line)
{
	int		j;
	char	*coord[4];

	coord[0] = "NO";
	coord[1] = "SO";
	coord[2] = "EA";
	coord[3] = "WE";
	j = 0;
	while (j < 4)
	{
		if (line[0] == coord[j][0] && line[1] == coord[j][1])
			return (j);
		j++;
	}
	return (-1);
}

int	parse_textures(char **lines, t_map *map)
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
			{
				error("Duplicated texture");
				return (-1);
			}
		}
		i++;
	}
	return (validate_textures(map->textures));
}
