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

void hit_compass(t_ray *ray, t_maze *maze)
{
    ray->compass[0] = touch(ray->hit_point.x, ray->hit_point.y - 1, maze);
    ray->compass[1] = touch(ray->hit_point.x, ray->hit_point.y + 1, maze);
    ray->compass[2] = touch(ray->hit_point.x + 1, ray->hit_point.y, maze);
    ray->compass[3] = touch(ray->hit_point.x - 1, ray->hit_point.y, maze);
}

void draw_rays(t_maze *maze, t_player *player)
{
    double fov;
    int wall_ax;
    double angle_step;
    int i;
    double ray_angle;
    int corner_detected;

    fov = 66 * M_PI / 180;
    angle_step = fov / (N_RAYS - 1); // angular increment
    i = 0;
    while (i < N_RAYS)
    {
        ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
        player->ray_x = player->x;
        player->ray_y = player->y;
        corner_detected = 0;

        // Check for internal corners while raycasting
        while (!(wall_ax = touch(player->ray_x, player->ray_y, maze)))
        {
            my_pixel_put((int)player->ray_x, (int)player->ray_y, &maze->img_2d, COLOR_YELLOW);
            player->ray_x = player->ray_x + cos(ray_angle);
            player->ray_y = player->ray_y + sin(ray_angle);
        }
        maze->ray[i]->hit_point.x = player->ray_x;
        maze->ray[i]->hit_point.y = player->ray_y;
        maze->ray[i]->angle = ray_angle;
        maze->ray[i]->dst = perp_wall_dst(player, ray_angle);
        hit_compass(maze->ray[i], maze);
        if (!corner_detected && wall_ax > 0)
        {
            draw_wall(maze->ray[i]->dst, maze, i, wall_ax); // Normal wall
        }
        i++;
    }
}

/* void draw_rays(t_maze *maze, t_player *player)
{
    double fov;
    int wall_ax;
    double angle_step;
    int i;
    double ray_angle;
    double wall_dst;
    int corner_detected;

    fov = 66 * M_PI / 180;
    angle_step = fov / (N_RAYS - 1); // angular increment
    i = 0;
    while (i < N_RAYS)
    {
        ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
        player->ray_x = player->x;
        player->ray_y = player->y;
        corner_detected = 0;

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
                corner_detected = 1;
                break; // Exit the ray casting loop since we found a corner
            }
            // Update ray position
            player->ray_x = next_x;
            player->ray_y = next_y;
        }
        double prev_x = player->ray_x - cos(ray_angle);
        double prev_y = player->ray_y - sin(ray_angle);
        if (!touch(prev_x, player->ray_y, maze) && !touch(player->ray_x, prev_y, maze))
            {
                wall_dst = perp_wall_dst(player, ray_angle);
                draw_wall(wall_dst, maze, i, 5); // Internal corner
                corner_detected = 1;
            }
        
        // If we hit a wall (not an internal corner), draw it normally
        if (!corner_detected && wall_ax > 0)
        {
            wall_dst = perp_wall_dst(player, ray_angle);
            draw_wall(wall_dst, maze, i, wall_ax); // Normal wall
        }
        
        i++;
    }
} */


/* void draw_rays(t_maze *maze, t_player *player)
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
                break; // Exit the ray casting loop since we found a corner
            }
            wall_dst = perp_wall_dst(player, ray_angle);
            draw_wall(wall_dst, maze, i, wall_ax);
        }
            //player->ray_x = next_x;
            //player->ray_y = next_y;
        }
        i++;
} */

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
