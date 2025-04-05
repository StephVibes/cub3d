/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:02:25 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 16:04:51 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_init_pos(t_maze *maze)
{
	int	i;
	int	j;

	i = 0;
	while (i < maze->map->height)
	{
		j = 0;
		while (j < maze->map->width)
		{
			if (is_player(maze->map->layout[i][j]))
			{
				maze->player.x = (j * BLOCK) + (BLOCK / 2);
				maze->player.y = (i * BLOCK) + (BLOCK / 2);
				maze->player.dir = maze->map->layout[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}

void	get_player_init_pos_minimap(t_maze *maze)
{
	int	i;
	int	j;

	i = 0;
	while (i < maze->map->height)
	{
		j = 0;
		while (j < maze->map->width)
		{
			if (is_player(maze->map->layout[i][j]))
			{
				maze->map->mini_player.x = maze->map->offset_2dx + 
					(j * maze->map->block) + (maze->map->block / 2);
				maze->map->mini_player.y = maze->map->offset_2dy + 
					(i * maze->map->block) + (maze->map->block / 2);
				maze->map->mini_player.dir = maze->map->layout[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}

void	get_player_angle(t_maze *maze)
{
	if (maze->player.dir == 'N')
	{
		maze->player.angle = (3 * M_PI) / 2;
		maze->map->mini_player.angle = (3 * M_PI) / 2;
	}
	else if (maze->player.dir == 'S')
	{
		maze->player.angle = M_PI / 2;
		maze->map->mini_player.angle = M_PI / 2;
	}
	else if (maze->player.dir == 'E')
	{
		maze->player.angle = 2 * M_PI;
		maze->map->mini_player.angle = 2 * M_PI;
	}
	else if (maze->player.dir == 'W')
	{
		maze->player.angle = M_PI;
		maze->map->mini_player.angle = M_PI;
	}
}
