#include <cub3d.h>

void	check_file(char *file)
{
	int	fd;
	char	buff[1];
	char	*ext;

	fd = open(file, O_RDONLY);
	ext = ft_strrchr(file, '.');
	if (!ext)
		error("Invalid texture file extension");
	if (fd < 0)
		error("Can't open file");
	if (read(fd, buff, 1) < 0)
		error("Can't read file");
	close(fd);
	if (ft_strncmp(ext, ".xpm", 4))
		error("Invalid texture file extension");
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
			break;
		}
		i++;
	}
}

void	validate_textures(char *textures[])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!textures[i])
			error("Texture data not found");
		remove_newline(textures[i]);
		i++;
	}
	i = 0;
	while (i < 4)
		check_file(textures[i++]);
}
