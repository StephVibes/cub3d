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

void draw_wall(t_ray *ray, t_maze *maze, int wall_ax)
{
	//double h;
	double y;
	double yy;
	double orig_y;
    int color;
    t_image *txt_img;


    txt_img = maze->map->txt_imgs[ray->coord];

	(void)wall_ax;
	//h = dst_to_h(dst);
    //h = (maze->map->block / ray->dst) * (WIDTH / 2);
	orig_y = (HEIGHT - ray->h) / 2; //for a given h, how much space is free up and down?
	yy = ray->h + orig_y;
    double ceiling = 0;
    double floor = yy;
	y = orig_y;
    while (ceiling < orig_y)
    {
        int ceiling_color = (maze->map->ceiling_color[0] << 16) | (maze->map->ceiling_color[1] << 8) | maze->map->ceiling_color[2];
        my_pixel_put(ray->ray_id, (int)ceiling, &maze->img_3d, ceiling_color);
        ceiling++;
    }
	while (y < yy)
	{
		if (ray->coord != -1)
        {
            int tex_y = (y - orig_y) / ray->factor_y;
            color = *(unsigned int *)(txt_img->data + txt_img->line_len * tex_y + (int)ray->txt_x * (txt_img->bpp / 8));
            my_pixel_put(ray->ray_id, (int)y, &maze->img_3d, color);
        }
		y++;
	}
    while (floor < HEIGHT)
    {
        int floor_color = (maze->map->floor_color[0] << 16) | (maze->map->floor_color[1] << 8) | maze->map->floor_color[2];
        my_pixel_put(ray->ray_id, (int)floor, &maze->img_3d, floor_color);
        floor++;
    }
}


double get_wall_dst(t_player *player ,double x, double y)
{
	double dst;

	dst = sqrt((y - player->y) * (y - player->y) + (x - player->x) * (x - player->x));
	return (dst);
}

int array_equals(int arr[], int expected[])
{
    int i;
    
    i = 0;
    while (i < 4)
    {
        if (arr[i] != expected[i])
            return 0;
        i++;
    }
    return 1;
}


void def_coord(t_ray *ray, t_maze *maze)
{

    (void)maze;

    int wall_facing_north[4] = {0, 1, 1, 1};    // Only North wall
    int wall_facing_south[4] = {1, 0, 1, 1};    // Only South wall
    int wall_facing_east[4] = {1, 1, 0, 1};     // Only East wall
    int wall_facing_west[4] = {1, 1, 1, 0};     // Only West wall

    if (array_equals(ray->compass, wall_facing_north))
        ray->coord = 0;
    else if (array_equals(ray->compass, wall_facing_south))
        ray->coord = 1;
    else if (array_equals(ray->compass, wall_facing_east))
        ray->coord = 2;
    else if (array_equals(ray->compass, wall_facing_west))
        ray->coord = 3;
    // else if (!touch(prev_x, ray->hit_point.y, maze) && !touch(ray->hit_point.x, prev_y, maze))
    // {
    //     if (ray->angle >= 0 && ray->angle <= M_PI/2)
    //         ray->coord = 3;
    //     else if(ray->angle >= M_PI/2 && ray->angle <= M_PI)
    //         ray->coord = 2;
    //     else if (ray->angle >= M_PI && ray->angle <= 3 * M_PI / 2)
    //         ray->coord = 1;
    //     else if (ray->angle >= 3 * M_PI / 2 && ray->angle <= 2 * M_PI)
    //         ray->coord = 0;
    // }
    else
        ray->coord = maze->ray[ray->ray_id - 1].coord;
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

    fov = 66 * M_PI / 180;
    angle_step = fov / (N_RAYS - 1); // angular increment
    i = 0;
    while (i < WIDTH)
    {
        ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
        player->ray_x = player->x;
        player->ray_y = player->y;

        // Check for internal corners while raycasting
        while (!(wall_ax = touch(player->ray_x, player->ray_y, maze)))
        {
            double next_x = player->ray_x + cos(ray_angle);
            double next_y = player->ray_y + sin(ray_angle);
            // Check for internal corners
             if (touch(next_x, player->ray_y, maze) && touch(player->ray_x, next_y, maze))
            {
                maze->ray[i].ray_id = i;
                maze->ray[i].coord = -1;
                maze->ray[i].hit_point.x = player->ray_x;
                maze->ray[i].hit_point.y = player->ray_y;
                maze->ray[i].angle = 0.0;
                maze->ray[i].angle = ray_angle;
                maze->ray[i].dst = perp_wall_dst(player, ray_angle);
                maze->ray[i].h = (BLOCK / maze->ray[i].dst) * (HEIGHT / 2);
                //maze->ray[i].h = (maze->map->block / maze->ray[i].dst) * (HEIGHT / 2);
                hit_compass(&maze->ray[i], maze);
                def_coord(&maze->ray[i], maze);
                determine_text(&maze->ray[i], maze);
                draw_wall(&maze->ray[i], maze, wall_ax);
                break; // Exit the ray casting loop since we found a corner
            }
            player->ray_x = next_x;
            player->ray_y = next_y;
        }
        maze->ray[i].ray_id = i;
        maze->ray[i].coord = -1; // Revisar porque esto borra la esquina
        maze->ray[i].hit_point.x = player->ray_x;
        maze->ray[i].hit_point.y = player->ray_y;
        maze->ray[i].angle = 0.0;
        maze->ray[i].angle = ray_angle;
        maze->ray[i].dst = perp_wall_dst(player, ray_angle);
        maze->ray[i].h = (BLOCK / maze->ray[i].dst) * (HEIGHT / 2);
        //maze->ray[i].h = (maze->map->block / maze->ray[i].dst) * (HEIGHT / 2);
        hit_compass(&maze->ray[i], maze);
        def_coord(&maze->ray[i], maze);
        determine_text(&maze->ray[i], maze);
        draw_wall(&maze->ray[i], maze, wall_ax); // Normal wall
        i++;
    }
}

void draw_rays_minimap(t_maze *maze, t_player *player)
{
    double fov;
    double angle_step;
    int i;
    double ray_angle;

    fov = 66 * M_PI / 180;
    angle_step = fov / (N_RAYS - 1); // angular increment
    i = 0;
    while (i < WIDTH)
    {
        ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
        player->ray_x = player->x;
        player->ray_y = player->y;

        // Check for internal corners while raycasting
        while (!(touch_minimap(player->ray_x, player->ray_y, maze)))
        {
            my_pixel_put((int)player->ray_x, (int)player->ray_y, &maze->img_2d, COLOR_GREEN_1);
			player->ray_x += cos(ray_angle);
			player->ray_y += sin(ray_angle);
		}
        i++;
    }
}

int	draw_loop(t_maze *maze)
{
	move_player(&maze->player);
	move_player_minimap(&maze->map->mini_player, maze->map->block);
	clear_screen(&maze->img_3d);
	draw_rays(maze, &maze->player); // not really drawing rays but the logic for the raycasting and drawing the walls
	mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->img_3d.img_ptr, 0, 0);
    if (maze->show_minimap)
    {
		clear_screen(&maze->img_2d);
        draw_rays_minimap(maze, &maze->map->mini_player);
		draw_map(maze); //Maze is in the back, player is in the front.
		draw_player(maze);
		mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->img_2d.img_ptr, 40, HEIGHT - MAP_SIZE - 80);
	}
	return (0);
}
