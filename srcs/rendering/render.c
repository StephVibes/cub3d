#include "cub3d.h"

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
	double h;
	double y;
	double yy;
	double orig_y;

	//h = dst_to_h(dst);
	h = (maze->map->block / dst) * (WIDTH / 2);
	orig_y = (HEIGHT - h) / 2; //for a given h, how much space is free up and down?
	yy = h + orig_y;
	y = orig_y;
	while (y < yy)
	{
		my_pixel_put(ray, (int)y, &maze->img_3d, COLOR_RED);
		y++;
	}
}

/* void draw_wall( double dst, t_maze *maze, int ray)
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
	h = (maze->map->block / dst) * (WIDTH / 2);
	orig_y = (HEIGHT - h) / 2; //for a given h, how much space is free up and down?
	x = ray * col_w;
	xx =  x + col_w;//For a given ray, we know the x valu by multiplying ray by col width.
	yy = h + orig_y;
	while(x < xx)
	{	
		y = orig_y;
		while (y < yy)
		{
			my_pixel_put((int)x, (int)y, &maze->img_3d, COLOR_RED);
			y++;
		}
		x++;
	}
} */
double get_wall_dst(t_player *player ,double x, double y)
{
	double dst;

	dst = sqrt((y - player->y) * (y - player->y) + (x - player->x) * (x - player->x));
	return (dst);
}

void	draw_rays(t_maze *maze, t_player *player)
{
	double	fov;
	//int	num_rays;
	//int	num_rays;
	double	angle_step;
	int	i;
	double	ray_angle;
	double	wall_dst;

	fov = 66 * M_PI / 180; // 66° Rad. Field of View
	//num_rays = 6; // Num of rays
	angle_step = fov / (N_RAYS - 1); // angular increment
	fov = 66 * M_PI / 180; // 66° Rad. Field of View
	//num_rays = 6; // Num of rays
	angle_step = fov / (N_RAYS - 1); // angular increment
	i = 0;
	while (i < N_RAYS)
	{
		ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
		player->ray_x = player->x;
		player->ray_y = player->y;
		while (!touch(player->ray_x, player->ray_y, maze))
		{
			
			//my_pixel_put((int)player->ray_x, (int)player->ray_y, &maze->img_2d, COLOR_YELLOW); // Draw ray pixel
			player->ray_x += cos(ray_angle); // Move ray in x direction
			player->ray_y += sin(ray_angle); // Move ray in y direction
		}
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
	clear_screen(&maze->img_2d);
	clear_screen(&maze->img_3d);
	draw_rays(maze, &maze->player);
	draw_map(maze); //Maze is in the back, player is in the front.
	draw_player(maze);
	mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->img_3d.img_ptr, 0, 0);
	//mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->img_2d.img_ptr, 10, HEIGHT - MAP_SIZE - 10);
	return (0);
}
