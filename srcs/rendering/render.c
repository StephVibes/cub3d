#include "cub3d.h"

void draw_ceiling (t_maze *maze, t_ray *ray, double orig_y)
{
    double ceiling;

    ceiling = 0;
    while (ceiling < orig_y)
    {
        my_pixel_put(ray->ray_id, (int)ceiling, &maze->img_3d, maze->map->ceiling_color);
        ceiling++;
    }
}

void draw_floor (t_maze *maze, t_ray *ray)
{
    double floor;

    while (floor < HEIGHT)
    {
        my_pixel_put(ray->ray_id, (int)floor, &maze->img_3d, maze->map->floor_color);
        floor++;
    }

}

void draw_line (t_maze *maze, t_ray *ray, double orig_y, double yy)
{
    double y;
    int color;
    int tex_y;
    t_image *txt_img;

    txt_img = maze->map->txt_imgs[ray->coord];
    y = orig_y;
    while (y < yy)
	{
		if (ray->coord != -1)
        {
            tex_y = (y - orig_y) / ray->factor_y;
            color = *(unsigned int *)(txt_img->data + txt_img->line_len * tex_y + (int)ray->txt_x * (txt_img->bpp / 8));
            my_pixel_put(ray->ray_id, (int)y, &maze->img_3d, color);
        }
		y++;
	}

}

void draw_wall(t_ray *ray, t_maze *maze)
{
	double  yy;
	double  orig_y;
    
	orig_y = (HEIGHT - ray->h) / 2;
	yy = ray->h + orig_y;
    draw_ceiling(maze, ray, orig_y);
    draw_floor(maze, ray);
    draw_line (maze, ray, orig_y, yy);
}

void draw_rays(t_maze *maze, t_player *player)
{
    double fov;
    int wall_ax;
    double angle_step;
    int i;
    double ray_angle;

    fov = 66 * M_PI / 180;
    angle_step = fov / (N_RAYS - 1);
    i = 0;
    while (i < WIDTH)
    {
        ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
        player->ray_x = player->x;
        player->ray_y = player->y;
        while (!(wall_ax = touch(player->ray_x, player->ray_y, maze)))
        {
            my_pixel_put((int)player->ray_x, (int)player->ray_y, &maze->img_2d, COLOR_YELLOW);
            double next_x = player->ray_x + cos(ray_angle);
            double next_y = player->ray_y + sin(ray_angle);
             if (touch(next_x, player->ray_y, maze) && touch(player->ray_x, next_y, maze))
            {
                ray_data(maze, i, ray_angle, player);
                hit_compass(&maze->ray[i], maze);
                def_coord(&maze->ray[i], maze);
                determine_text(&maze->ray[i], maze);
                draw_wall(&maze->ray[i], maze);
                break;
            }
            player->ray_x = next_x;
            player->ray_y = next_y;
        }
        ray_data(maze, i, ray_angle, player);
        hit_compass(&maze->ray[i], maze);
        def_coord(&maze->ray[i], maze);
        determine_text(&maze->ray[i], maze);
        draw_wall(&maze->ray[i], maze);
        i++;
    }
}

int	draw_loop(t_maze *maze)
{
	move_player(&maze->player);
	clear_screen(&maze->img_2d);
	clear_screen(&maze->img_3d);
	draw_rays(maze, &maze->player);
	draw_map(maze);
	draw_player(maze);
	mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->img_3d.img_ptr, 0, 0);
	//mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->img_2d.img_ptr, 10, HEIGHT - MAP_SIZE - 10);
	return (0);
}
