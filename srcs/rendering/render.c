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

void draw_wall( double dst, t_maze *maze, int ray, int wall_ax)
{
	double h;
	double y;
	double yy;
	double orig_y;

	(void)wall_ax;
	//h = dst_to_h(dst);
	h = (maze->map->block / dst) * (WIDTH / 2);
	orig_y = (HEIGHT - h) / 2; //for a given h, how much space is free up and down?
	yy = h + orig_y;
	y = orig_y;
	while (y < yy)
	{
		if (wall_ax == 1)
			my_pixel_put(ray, (int)y, &maze->img_3d, COLOR_GREEN);
		else if (wall_ax == 2)
			my_pixel_put(ray, (int)y, &maze->img_3d, COLOR_RED);
		else if (wall_ax == 3)
			my_pixel_put(ray, (int)y, &maze->img_3d, COLOR_MAGENTA);
		else if (wall_ax == 4) // Corner
            my_pixel_put(ray, (int)y, &maze->img_3d, COLOR_YELLOW);
		else if (wall_ax == 5) // External Corner
            my_pixel_put(ray, (int)y, &maze->img_3d, COLOR_CYAN);
		y++;
	}
}

double get_wall_dst(t_player *player ,double x, double y)
{
	double dst;

	dst = sqrt((y - player->y) * (y - player->y) + (x - player->x) * (x - player->x));
	return (dst);
}

void draw_rays(t_maze *maze, t_player *player)
{
    double fov;
    int wall_ax;
    double angle_step;
    int i;
    double ray_angle;
    double wall_dst;

    fov = 66 * M_PI / 180;
    angle_step = fov / (N_RAYS - 1); // angular increment
    i = 0;
    while (i < N_RAYS)
    {
        ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
        player->ray_x = player->x;
        player->ray_y = player->y;
        bool corner_handled = false;

        // Check for internal corners while raycasting
        while (!(wall_ax = touch(player->ray_x, player->ray_y, maze)))
        {
            my_pixel_put((int)player->ray_x, (int)player->ray_y, &maze->img_2d, COLOR_YELLOW);
            double next_x = player->ray_x + cos(ray_angle);
            double next_y = player->ray_y + sin(ray_angle);
            
            // Check for internal corners
            if (touch(next_x, player->ray_y, maze) && touch(player->ray_x, next_y, maze))
            {
                wall_dst = perp_wall_dst(player, ray_angle);
                draw_wall(wall_dst, maze, i, 4); // Internal corner
                corner_handled = true;
                break; // Exit the ray casting loop since we found a corner
            }
            
            player->ray_x = next_x;
            player->ray_y = next_y;
        }

        // If we didn't handle an internal corner, check for wall hit and external corners
        if (!corner_handled)
        {
            // Now wall_ax > 0, we've hit something
            // Check for external corner
            double prev_x = player->ray_x - cos(ray_angle);
            double prev_y = player->ray_y - sin(ray_angle);

            double perp_x_offset = -sin(ray_angle) * 0.1;
            double perp_y_offset = cos(ray_angle) * 0.1;

            // Check both sides perpendicular to the ray
            bool is_external_corner = 
                (touch(prev_x + perp_x_offset, prev_y + perp_y_offset, maze) > 0) != 
                (touch(prev_x - perp_x_offset, prev_y - perp_y_offset, maze) > 0);

            wall_dst = perp_wall_dst(player, ray_angle);
            
            if (is_external_corner)
                draw_wall(wall_dst, maze, i, 5); // External corner
            else
                draw_wall(wall_dst, maze, i, wall_ax); // Regular wall
        }

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
	mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->img_2d.img_ptr, 10, HEIGHT - MAP_SIZE - 10);
	return (0);
}
