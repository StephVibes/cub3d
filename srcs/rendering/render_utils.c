#include "cub3d.h"

double perp_wall_dst(t_player *player, double ray_angle)
{
    double ray_dir_x, ray_dir_y;
    double ray_length;
    double correction_angle;
    
    ray_dir_x = player->ray_x - player->x;
    ray_dir_y = player->ray_y - player->y;
    ray_length = sqrt(ray_dir_x * ray_dir_x + ray_dir_y * ray_dir_y);
    correction_angle = ray_angle - player->angle;
    while (correction_angle > M_PI) 
        correction_angle -= 2 * M_PI;
    while (correction_angle < -M_PI)
        correction_angle += 2 * M_PI;
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
    double prev_x = ray->hit_point.x - cos(ray->angle);
    double prev_y = ray->hit_point.y - sin(ray->angle);

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
    if (!touch(prev_x, ray->hit_point.y, maze) && !touch(ray->hit_point.x, prev_y, maze))
    {
        if (ray->angle >= 0 && ray->angle < M_PI/2)
            ray->coord = 3;
        else if(ray->angle >= M_PI/2 && ray->angle < M_PI)
            ray->coord = 2;
        else if (ray->angle >= M_PI && ray->angle < 3 * M_PI / 2)
            ray->coord = 1;
        else if (ray->angle >= 3 * M_PI / 2 && ray->angle < 2 * M_PI)
            ray->coord = 0;
    }
}


void hit_compass(t_ray *ray, t_maze *maze)
{
    ray->compass[0] = touch(ray->hit_point.x, ray->hit_point.y - 1, maze);
    ray->compass[1] = touch(ray->hit_point.x, ray->hit_point.y + 1, maze);
    ray->compass[2] = touch(ray->hit_point.x + 1, ray->hit_point.y, maze);
    ray->compass[3] = touch(ray->hit_point.x - 1, ray->hit_point.y, maze);
}

void ray_data (t_maze *maze, int i, double ray_angle, t_player *player)
{
    maze->ray[i].ray_id = i;
    maze->ray[i].coord = -1;
    maze->ray[i].hit_point.x = player->ray_x;
    maze->ray[i].hit_point.y = player->ray_y;
    maze->ray[i].angle = 0.0;
    maze->ray[i].angle = ray_angle;
    maze->ray[i].dst = perp_wall_dst(player, ray_angle);
    maze->ray[i].h = (maze->map->block / maze->ray[i].dst) * (HEIGHT / 2);
}
