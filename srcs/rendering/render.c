#include "cub3d.h"

static void	my_pixel_put(int x, int y, t_image *screen, int color)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	int	offset;

	offset = (y * screen->line_len) + (x * (screen->bpp / 8));
	*(unsigned int *)(screen->data + offset) = color;
}

void	draw_square(int x, int y, int size, int color, t_image *screen)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_pixel_put(x + i, y + j, screen, color);
			j++;
		}
		i++;
	}
}

void	move_player(t_player *player)
{
	int	speed;
	double	angle_speed;
	double	cos_angle;
	double	sin_angle;

	speed = 2;
	angle_speed = 0.1;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->angle > 2 * M_PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * M_PI;
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

void	clear_screen(t_image *screen)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			my_pixel_put(i, j, screen, 0x00000000);
			j++;
		}
		i++;
	}
}

void	draw_rays(t_maze *maze, t_player *player)
{
	double	fov;
	int	num_rays;
	double	angle_step;
	int	i;
	double	ray_angle;

	fov = M_PI / 2; // 90° Field of View
	num_rays = 180; // Num of rays
	angle_step = fov / (num_rays - 1); // angular increment
	i = 0;
	while (i < num_rays)
	{
		ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
		player->ray_x = player->x;
		player->ray_y = player->y;
        // Cast the ray
		while (!touch(player->ray_x, player->ray_y, maze))
		{
			my_pixel_put((int)player->ray_x, (int)player->ray_y, &maze->screen, 0xFFFFFF00); // Draw ray pixel
			player->ray_x += cos(ray_angle); // Move ray in x direction
			player->ray_y += sin(ray_angle); // Move ray in y direction
		}
		i++;
	}
}

float distance(float x, float y){
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_maze *maze)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - maze->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

void	draw_line(t_player *player, t_maze *maze, float start_x, int i)
{
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;

    while (!touch(ray_x, ray_y, maze))
    {
	    if (maze->mode == 0)
		my_pixel_put(ray_x, ray_y, &maze->screen, 0xFFFFFF00);
	    ray_x += cos_angle;
	    ray_y += sin_angle;
    }
    if (maze->mode == 1)
    {
        float dist = fixed_dist(player->x, player->y, ray_x, ray_y, maze);
        float height = (SQUARE / dist) * (WIDTH / 2);
        int start_y = (HEIGHT - height) / 2;
        int end = start_y + height;
        while(start_y < end)
        {
            my_pixel_put(i, start_y, &maze->screen, 0xFF0000);
            start_y++;
        }
    }
}

int	draw_loop(t_maze *maze)
{
	move_player(&maze->player);
	clear_screen(&maze->screen);
//	draw_square(maze->player.x, maze->player.y, 10, 0x00FF0000, &maze->screen);
//	draw_map(maze);
//	draw_rays(maze, &maze->player);
	if (maze->mode == 0)
	{
		draw_square(maze->player.x, maze->player.y, 10, 0x00FF0000, &maze->screen); // improve
		draw_map(maze);
	}
	float fraction = M_PI / 2 / WIDTH;
	float start_x = maze->player.angle - M_PI / 3;
	int i = 0;
	while(i < WIDTH)
	{
		draw_line(&maze->player, maze, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->screen.img_ptr, 0, 0);
	return (0);
}
