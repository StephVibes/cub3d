/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key_press.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:41:22 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:01:09 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement_keys_press(int keycode, t_maze *maze)
{
	if (keycode == XK_w)
	{
		maze->player.key_state[0] = 1;
		maze->map->mini_player.key_state[0] = 1;
	}
	if (keycode == XK_s)
	{
		maze->player.key_state[1] = 1;
		maze->map->mini_player.key_state[1] = 1;
	}
	if (keycode == XK_a)
	{
		maze->player.key_state[2] = 1;
		maze->map->mini_player.key_state[2] = 1;
	}
	if (keycode == XK_d)
	{
		maze->player.key_state[3] = 1;
		maze->map->mini_player.key_state[3] = 1;
	}
}

static void	handle_rotation_keys_press(int keycode, t_maze *maze)
{
	if (keycode == XK_Right)
	{
		maze->player.right_rotate = 1;
		maze->map->mini_player.right_rotate = 1;
	}
	if (keycode == XK_Left)
	{
		maze->player.left_rotate = 1;
		maze->map->mini_player.left_rotate = 1;
	}
}

int	key_press_handler(int keycode, t_maze *maze)
{
	handle_movement_keys_press(keycode, maze);
	handle_rotation_keys_press(keycode, maze);
	if (keycode == XK_Escape)
		close_handler(maze);
	if (keycode == XK_space)
	{
		if (maze->show_minimap == 0)
			maze->show_minimap = 1;
		else
			maze->show_minimap = 0;
	}
	return (0);
}
