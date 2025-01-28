#include <cub3d.h>

int	check_file(char *file)
{
	int	fd;
	char	buff[1];
	char	*ext;

	printf("file: '%s'", file);
	fd = open(file, O_RDONLY);
	ext = ft_strrchr(file, '.');
	if (!ext)
	{
		printf("Invalid texture file extension\n");
		return (1);
	}
	if (fd < 0)
	{
		printf("can't open file\n");
		return (1);
	}
	if (read(fd, buff, 1) < 0)
	{
		printf("can't read file\n");
		return (1);
	}
	close(fd);
	if (ft_strncmp(ext, ".xpm", 4))
	{
		printf("Invalid texture file extension\n");
		return (1);
	}
	return (0);
}

void	remove_newline(char *str)
{
	int	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			break;
		}
		i++;
	}
}

int	validate_textures(char *textures[])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!textures[i])
		{
			printf("Error\nMissing texture\n");
			return (1);
		}
		remove_newline(textures[i]);
		i++;
	}
	if (check_file(textures[0]) || check_file(textures[1]) || check_file(textures[2]) || check_file(textures[3]))
	{
		//printf("Error\nInvalid texture file\n");
		return (1);
	}
	return (0);
}