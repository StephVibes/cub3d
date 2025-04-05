/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:14:40 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 16:18:36 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_xpm(t_image *img, t_maze *maze)
{
	if (img)
	{
		mlx_destroy_image(maze->mlx_ptr, img->img_ptr);
		free(img);
	}
}

void	init_txt_image(t_maze *maze, t_image *img, char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(maze->mlx_ptr, path, 
			&img->width, &img->height);
	if (!img)
	{
		mlx_destroy_window(maze -> mlx_ptr, maze -> win_ptr);
		mlx_destroy_display(maze -> mlx_ptr);
		free(maze -> mlx_ptr);
		error("error creating texture image with minilibx");
	}
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, 
			&img->line_len, &img->endian);
	return ;
}

void	get_images_xpm(t_map *map, t_maze *maze)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		init_txt_image(maze, map->txt_imgs[i], map->textures[i]);
		if (!map->txt_imgs[i])
		{
			error("Failed to parse XPM texture");
			while (j < i)
			{
				free_xpm(map->txt_imgs[j], maze);
				map->txt_imgs[j] = NULL;
			}
			return ;
		}
		i++;
	}
}
