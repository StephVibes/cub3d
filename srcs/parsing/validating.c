#include "cub3d.h"

int	check_textures(char **textures)
{
	int	i;

	while (textures[i])
	{
		if (check_texture(textures[i]))
			i++;
		else
			perror("texture is not valid");
	}
}


