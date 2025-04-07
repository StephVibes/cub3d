/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:52:33 by alramire          #+#    #+#             */
/*   Updated: 2025/04/07 11:15:53 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	check_file(char *file)
{
	int		fd;
	char	buff[1];
	char	*ext;

	fd = open(file, O_RDONLY);
	ext = ft_strrchr(file, '.');
	if (!ext)
	{
		return (error("Invalid texture file extension"), -1);
	}
	if (fd < 0)
	{
		return (error("Can't open file"), -1);
	}
	if (read(fd, buff, 1) < 0)
	{
		return (error("Can't read file"), -1);
		//return (-1);
	}
	close(fd);
	if (ft_strncmp(ext, ".xpm", 4))
	{
		return (error("Invalid texture file extension"), -1);
		//return (-1);
	}
	return (0);
}

void	remove_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
}

int	validate_textures(char *textures[])
{
	int	i;
	int	result;

	i = 0;
	while (i < 4)
	{
		if (!textures[i])
		{
			error("Texture data not found");
			return (-1);
		}
		remove_newline(textures[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		result = check_file(textures[i++]);
		if (result == -1)
			return (result);
	}
	return (result);
}
