/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:49:33 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 16:56:03 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_rotate(t_player *player)
{
	if (player->right_rotate)
		player->angle += ANGLE_SPEED;
	if (player->left_rotate)
		player->angle -= ANGLE_SPEED;
	if (player->angle > 2 * M_PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * M_PI;
}

void	move_player_bf(t_player *player, double cos_angle, 
		double sin_angle, double speed)
{
	if (player->key_state[0])
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_state[1])
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_state[2])
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->key_state[3])
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
}

void	move_player(t_player *player)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move_player_rotate(player);
	move_player_bf(player, cos_angle, sin_angle, SPEED);
}

void	move_player_minimap(t_player *player, int block_map)
{
	double	speed;
	double	cos_angle;
	double	sin_angle;

	speed = SPEED * ((double)block_map / BLOCK);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move_player_rotate(player);
	move_player_bf(player, cos_angle, sin_angle, speed);
}
