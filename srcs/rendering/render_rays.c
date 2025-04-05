#include "cub3d.h"

/* void draw_ceiling (t_maze *maze, t_ray *ray, double orig_y)
{
    double ceiling;

    ceiling = 0;
    while (ceiling < orig_y)
    {
        my_pixel_put(ray->ray_id, (int)ceiling, &maze->img_3d, maze->map->ceiling_color);
        ceiling++;
    }
}

void draw_floor (t_maze *maze, t_ray *ray, double floor)
{
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

void draw_utils(t_ray *ray, t_maze *maze)
{
	double  yy;
	double  orig_y;
    
	orig_y = (HEIGHT - ray->h) / 2;
	yy = ray->h + orig_y;
    draw_ceiling(maze, ray, orig_y);
    draw_floor(maze, ray, yy);
    draw_line (maze, ray, orig_y, yy);
}

void draw_wall (t_maze *maze, int i, double ray_angle)
{
    ray_data(maze, i, ray_angle, &maze->player);
    hit_compass(&maze->ray[i], maze);
    def_coord(&maze->ray[i], maze);
    determine_text(&maze->ray[i], maze);
    draw_utils(&maze->ray[i], maze);
} */

void while_touch(t_player *player, t_maze *maze, double ray_angle, int i)
{
    double next_x;
    double next_y;

    while (!(touch(player->ray_x, player->ray_y, maze)))
    {
        next_x = player->ray_x + cos(ray_angle);
        next_y = player->ray_y + sin(ray_angle);
        if (touch(next_x, player->ray_y, maze) && touch(player->ray_x, next_y, maze))
        {
            draw_wall (maze, i, ray_angle);
            break;
        }
        player->ray_x = next_x;
        player->ray_y = next_y;
    }
    draw_wall (maze, i, ray_angle);
}

void while_touch_minimap(t_player *player, t_maze *maze, double ray_angle)
{
    double next_x;
    double next_y;

    while (!(touch_minimap(player->ray_x, player->ray_y, maze)))
        {
            my_pixel_put((int)player->ray_x, (int)player->ray_y, &maze->img_2d, COLOR_GREEN_1);
			next_x = player->ray_x + cos(ray_angle);
            next_y = player->ray_y + sin(ray_angle);
            if (touch_minimap(next_x, player->ray_y, maze) && touch_minimap(player->ray_x, next_y, maze))
            {
                break;
            }
            player->ray_x = next_x;
            player->ray_y = next_y;
		}
}

void draw_rays(t_maze *maze, t_player *player)
{
    double angle_step;
    int i;
    double ray_angle;

    angle_step = FOV / (N_RAYS - 1);
    i = 0;
    while (i < WIDTH)
    {
        ray_angle = player->angle - (FOV / 2) + (i * angle_step); // Calculate ray angle
        player->ray_x = player->x;
        player->ray_y = player->y;
        while_touch(player, maze, ray_angle, i);
        i++;
    }
}



void draw_rays_minimap(t_maze *maze, t_player *player)
{
    double angle_step;
    int i;
    double ray_angle;

    angle_step = FOV / (N_RAYS - 1);
    i = 0;
    while (i < WIDTH)
    {
        ray_angle = player->angle - (FOV / 2) + (i * angle_step);
        player->ray_x = player->x;
        player->ray_y = player->y;
        while_touch_minimap(player, maze, ray_angle);
        i++;
    }
}

/* int	draw_loop(t_maze *maze)
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
} */
