/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key_release.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:41:22 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:01:39 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement_keys_release(int keycode, t_maze *maze)
{
	if (keycode == XK_w)
	{
		maze->player.key_state[0] = 0;
		maze->map->mini_player.key_state[0] = 0;
	}
	if (keycode == XK_s)
	{
		maze->player.key_state[1] = 0;
		maze->map->mini_player.key_state[1] = 0;
	}
	if (keycode == XK_a)
	{
		maze->player.key_state[2] = 0;
		maze->map->mini_player.key_state[2] = 0;
	}
	if (keycode == XK_d)
	{
		maze->player.key_state[3] = 0;
		maze->map->mini_player.key_state[3] = 0;
	}
}

static void	handle_rotation_keys_release(int keycode, t_maze *maze)
{
	if (keycode == XK_Right)
	{
		maze->player.right_rotate = 0;
		maze->map->mini_player.right_rotate = 0;
	}
	if (keycode == XK_Left)
	{
		maze->player.left_rotate = 0;
		maze->map->mini_player.left_rotate = 0;
	}
}

int	key_release_handler(int keycode, t_maze *maze)
{
	handle_movement_keys_release(keycode, maze);
	handle_rotation_keys_release(keycode, maze);
	return (0);
}
