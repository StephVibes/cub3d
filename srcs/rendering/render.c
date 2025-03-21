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

	speed = 1;
	angle_speed = 0.01;
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

double perp_wall_dst(t_player *player, double ray_angle)
{
    double ray_dir_x, ray_dir_y;
    double ray_length;
    double correction_angle;
    
    // Calculate ray direction vector
    ray_dir_x = player->ray_x - player->x;
    ray_dir_y = player->ray_y - player->y;
    
    // Calculate ray length (straight-line distance)
    ray_length = sqrt(ray_dir_x * ray_dir_x + ray_dir_y * ray_dir_y);
    
    // Calculate angle difference for fisheye correction
    // This is the angle between the ray and the player's viewing direction
    correction_angle = ray_angle - player->angle;
    
    // Normalize correction_angle to be between -π and π
    while (correction_angle > M_PI) correction_angle -= 2 * M_PI;
    while (correction_angle < -M_PI) correction_angle += 2 * M_PI;
    
    // Apply fisheye correction by multiplying by cosine of the angle difference
    return ray_length * cos(correction_angle);
}

double get_wall_distance(t_player *player)
{
	double dst;

	dst = sqrt((player->ray_y - player->y) * (player->ray_y - player->y) + (player->ray_x - player->x) * (player->ray_x - player->x));
	return (dst);
}

double dst_to_h(double dst)
{
	double h;
	double slope;

	slope = (MIN_WALL - HEIGHT) / (MAX_DST);
	h = slope * dst + HEIGHT;
	if (dst > MAX_DST)
		return(MIN_WALL);
	return (h);
}

void draw_wall( double dst, t_maze *maze, int ray)
{
	double col_w;
	double h;
	int x;
	int xx;
	int y;
	int yy;
	int orig_y;

	col_w = WIDTH / N_RAYS;
	//h = dst_to_h(dst);
	h = (SQUARE / dst) * (WIDTH / 2);
	orig_y = (HEIGHT - h) / 2; //for a given h, how much space is free up and down?
	x = ray * col_w;
	xx =  x + col_w;//For a given ray, we know the x valu by multiplying ray by col width.
	yy = h + orig_y;
	while(x < xx)
	{	
		y = orig_y;
		while (y < yy)
		{
			my_pixel_put((int)x, (int)y, &maze->screen, COLOR_RED);
			y++;
		}
		x++;
	}
}
double get_wall_dst(t_player *player ,double x, double y)
{
	double dst;

	dst = sqrt((y - player->y) * (y - player->y) + (x - player->x) * (x - player->x));
	return (dst);
}


void wall_segment_init(t_maze *maze, int i)
{
	if(maze->wall_seg[0] == 0.0)
	{
		maze->wall_seg[0] = maze->player.ray_x;
		maze->wall_seg[1] = maze->player.ray_y;
		maze->wall_seg[2] = i;
		return;
	}
	else if(maze->wall_seg[3] == 0.0)
	{
		maze->wall_seg[3] = maze->player.ray_x;
		maze->wall_seg[4] = maze->player.ray_y;
		maze->wall_seg[5] = i;
		return;
	}
	wall_segment(maze, i);
}


void	draw_rays(t_maze *maze, t_player *player)
{
	double	fov;
	//int	num_rays;
	double	angle_step;
	int	i;
	double	ray_angle;
	double	wall_dst;

	fov = 66 * M_PI / 180; // 66° Rad. Field of View
	//num_rays = 6; // Num of rays
	angle_step = fov / (N_RAYS - 1); // angular increment
	i = 0;
	while (i < N_RAYS)
	{
		ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
		player->ray_x = player->x;
		player->ray_y = player->y;
        // Cast the ray
		while (!touch(player->ray_x, player->ray_y, maze))
		{
			
			//my_pixel_put((int)player->ray_x, (int)player->ray_y, &maze->screen, COLOR_YELLOW); // Draw ray pixel
			player->ray_x += cos(ray_angle); // Move ray in x direction
			player->ray_y += sin(ray_angle); // Move ray in y direction
		}
		//wall_segment_init(maze, i);
		//we need to compare if the ray is moving in x or in y
		// we need to flag when it changing from one or the other.
		//dprintf(maze->fd_log, "(x:%.2f, y:%.2f)\n",player->ray_x, player->ray_y);
		wall_dst = perp_wall_dst(player, ray_angle);
		draw_wall(wall_dst, maze, i);
		//wall_dst = get_wall_distance(player);
		//draw_wall(wall_dst, maze, i);
		i++;
	}
}

int	draw_loop(t_maze *maze)
{
	move_player(&maze->player);
	clear_screen(&maze->screen);
	//draw_map(maze); //Maze is in the back, player is in the front.
	//draw_square(maze->player.x, maze->player.y, 10, 0x00FF0000, &maze->screen);
	//draw_map(maze); //Player is in the back, maze is in the front.
	draw_rays(maze, &maze->player);
	mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->screen.img_ptr, 0, 0);
	return (0);
}
