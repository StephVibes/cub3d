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
			my_pixel_put((int)x, (int)y, &maze->img_3d, COLOR_RED);
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

double find_slope(double x, double y, double xx, double yy)
{
	double m;
	
	m = (yy - y) / (xx - x);
	return (m);
}

double find_intercept(double m, double x, double y)
{
	double b;
	b = y - m * x;
	return (b);
}

/* double find_y(double x, double y, double )
{
	double y;
	double m; //slope
	double b; //intercept

	m = (maze->wall_seg[4] - maze->wall_seg[1]) / (maze->wall_seg[3] - maze->wall_seg[0]);
	b = maze->wall_seg[1] - m * maze->wall_seg[0];
	y = m * x + b;
	return (y);
} */

void draw_wall_segment(t_maze *maze)
{
	(void)maze;
	double col_w;
	double x;
	double y;
	double xx;
	double yy;
	double w;
	double ww;
	double m;
	double b;
	double h;
	double hh;
	int i = 0;

	col_w = WIDTH / N_RAYS;
	while(i <= maze->segments)
	{
		w = get_wall_dst(&maze->player, maze->w[i].st.x, maze->w[i].st.y);
		ww = get_wall_dst(&maze->player, maze->w[i].end.x, maze->w[i].end.y);
		h = dst_to_h(w);
		hh = dst_to_h(ww);
		y = (HEIGHT - h) / 2; //for a given h, how much space is free up and down?
		x = maze->w[i].st.ray * col_w; //For a given ray, we know the x valu by multiplying ray by col width.
		yy = (HEIGHT - hh) / 2;
		xx = maze->w[i].end.ray * col_w;
		m = find_slope(x, y, xx, yy);
		b = find_intercept(m, x, y);
		while(x <= xx)
		{
			yy = (HEIGHT - y);
			while(y <=  yy)
			{
				my_pixel_put((int)x, (int)y, &maze->img_3d, COLOR_GREEN);
				y++;
			}
			x++;
			y = m * x + b;
		}
		i++;
	}
	/* printf("segment1end: x:%0.2f, y:%0.2f\n", x, y);
	printf("segment2end: xx:%0.2f, yy:%0.2f\n", xx, yy); */
}

void segment_init(t_maze *maze, t_point p)
{
	int *seg;

	seg = &maze->segments;
	maze->w[*seg].st = p;
}

void segment_end(t_maze *maze, t_point p)
{
	int *seg;

	seg = &maze->segments;
	maze->w[*seg].end = p;
	(*seg)++; //who should initializes the new segment? the start or the end?
}

void wall_segment_end(t_maze *maze, int i)
{
	int		*seg;
	double	dx;
	double	dy;

	seg = &maze->segments;
	dx = fabs(maze->w[*seg].end.x - maze->w[*seg].st.x);
	dy = fabs(maze->w[*seg].end.y - maze->w[*seg].st.y);
	if(dx > dy)
		maze->w[*seg].delta = 'x';
	maze->w[*seg].delta = 'y'; 
	maze->w[*seg].end.x = maze->player.ray_x;
	maze->w[*seg].end.y = maze->player.ray_y;
	maze->w[*seg].end.ray = i;
	maze->w[*seg].end.dst = get_wall_dst (&maze->player, maze->w[*seg].end.x, maze->w[*seg].end.y);
	(*seg)++; //who should initializes the new segment? the start or the end?
}

int get_end_dst(t_maze *maze)
{
	if(maze->delta.p2.dst < 2)
	{
		if (maze->delta.p3.dst < 2)
		{
			if(maze->delta.p4.dst < 2)
				return (0);
			else
				return (1);
		}
		return (3);
	}
	return(2);
}

void wall_deltas(t_maze *maze, int i)
{
	int *seg;

	seg = &maze->segments;
	maze->delta.p4.x = maze->player.ray_x;
	maze->delta.p4.y = maze->player.ray_y;
	maze->delta.p4.ray = i;
	maze->delta.p4.dst = get_wall_dst(&maze->player, maze->delta.p4.x, maze->delta.p4.y);
	
	if(maze->delta.p1.dst < 2)
	{
		if(get_end_dst(maze))
		{
			//maze->w[maze->segments].end = maze->delta.p4;
			wall_segment_end(maze, i);
			segment_init(maze, maze->delta.p4);
			//wall_segment_init(maze, i);
			init_wall_delta(maze);
			maze->delta.p1 = maze->w[*seg].st;
			return ;
		}
		return;
	}
	maze->delta.dx1 = fabs(maze->delta.p2.x - maze->delta.p1.x);
	maze->delta.dx2 = fabs(maze->delta.p3.x - maze->delta.p2.x);
	maze->delta.dx3 = fabs(maze->delta.p4.x - maze->delta.p3.x);
	maze->delta.dy1 = fabs(maze->delta.p2.y - maze->delta.p1.y);
	maze->delta.dy2 = fabs(maze->delta.p3.y - maze->delta.p2.y);
	maze->delta.dy3 = fabs(maze->delta.p4.y - maze->delta.p3.y);
	
		if(maze->delta.dx1 > maze->delta.dy1) // x 
	{
		if(maze->delta.dx2 > maze->delta.dy2) // xx
		{
			if(maze->delta.dx3 > maze->delta.dy3) // xxx
			{
				if(i == N_RAYS)
					segment_end(maze, maze->delta.p4);
				init_wall_delta(maze);
				maze->w[(*seg)].delta = 'x';
				//3 consecutive x deltas are bigger than y, then the 4 points belong to same x line.
			}
			else // xxy
			{
				maze->delta.p1 = maze->delta.p2;
				maze->delta.p2 = maze->delta.p3;
				maze->delta.p3 = maze->delta.p4;
				ft_memset(&maze->delta.p4, 0, sizeof(t_point));
				// p3 and p4 show a change in direction
				// I can delete p1 and p2 and enter 2 more points to compare.
			}
		}
		else //xy
		{
			if(maze->delta.dx3 < maze->delta.dy3) //xyy
			{
				if (maze->w[(*seg)].delta == 'y')
					init_wall_delta(maze);
				else
				{
					// start segment
					//
					//Breakpoint here
					segment_end(maze, maze->delta.p2);
					segment_init(maze, maze->delta.p3);
					maze->w[(*seg)].delta = 'y';
					init_wall_delta(maze);
				}
			}
			else //xyx
			{
				init_wall_delta(maze);
				//Make it more clear
			}
		}
	}
	else if(maze->delta.dx1 < maze->delta.dy1) // y 
	{
		if(maze->delta.dx2 < maze->delta.dy2) // yy
		{
			if(maze->delta.dx3 < maze->delta.dy3) // yyy
			{
				init_wall_delta(maze);
				maze->w[(*seg)].delta = 'y';
				//3 consecutive x deltas are bigger than y, then the 4 points belong to same x line.
			}
			else // yyx
			{
				maze->delta.p2 = maze->delta.p3;
				maze->delta.p3 = maze->delta.p4;
				ft_memset(&maze->delta.p4, 0, sizeof(t_point));
				// p3 and p4 show a change in direction
				// I can delete p1 and p2 and enter 2 more points to compare.
			}
		}
		else //yx ray 175 started new segment, it should not.
		{
			if(maze->delta.dx3 > maze->delta.dy3) //yxx
			{
				if (maze->w[(*seg)].delta == 'x')
					init_wall_delta(maze);
				else
				{
					// start segment
					//everytime we start a segment, we need to finish the previous one.
					segment_end(maze, maze->delta.p2);
					segment_init(maze, maze->delta.p3);
					maze->w[(*seg)].delta = 'x';
					init_wall_delta(maze);
				}
			}
			else //yxy
			{
				init_wall_delta(maze);
				//Make it more clear
			}
		}
	}
	
}

void wall_segment(t_maze *maze, int i)
{
	if(maze->delta.p1.x == 0)
	{
		maze->delta.p1.x = maze->player.ray_x;
		maze->delta.p1.y = maze->player.ray_y;
		maze->delta.p1.ray = i;
		maze->delta.p1.dst = get_wall_dst(&maze->player, maze->delta.p1.x, maze->delta.p1.y);
		return ;
	}
	else if(maze->delta.p2.x == 0)
	{
		maze->delta.p2.x = maze->player.ray_x;
		maze->delta.p2.y = maze->player.ray_y;
		maze->delta.p2.ray = i;
		maze->delta.p2.dst = get_wall_dst(&maze->player, maze->delta.p2.x, maze->delta.p2.y);
		return ;
	}
	else if(maze->delta.p3.x == 0)
	{
		maze->delta.p3.x = maze->player.ray_x;
		maze->delta.p3.y = maze->player.ray_y;
		maze->delta.p3.ray = i;
		maze->delta.p3.dst = get_wall_dst(&maze->player, maze->delta.p3.x, maze->delta.p3.y);
		return ;
	}
/* 	else if(maze->delta.p4.x == 0)
	{
		maze->delta.p4.x = maze->player.ray_x;
		maze->delta.p4.y = maze->player.ray_y;
		maze->delta.p4.ray = i;
		maze->delta.p4.dst = get_wall_dst(&maze->player, maze->delta.p4.x, maze->delta.p4.y);
		return ;
	}
	else if(maze->delta.p5.x == 0)
	{
		maze->delta.p5.x = maze->player.ray_x;
		maze->delta.p5.y = maze->player.ray_y;
		maze->delta.p5.x = i;
		maze->delta.p5.dst = get_wall_dst(&maze->player, maze->delta.p5.x, maze->delta.p5.y);
		return ;
	}
	else if(maze->delta.p6.x == 0)
	{
		maze->delta.p6.x = maze->player.ray_x;
		maze->delta.p6.y = maze->player.ray_y;
		maze->delta.p6.x = i;
		maze->delta.p6.dst = get_wall_dst(&maze->player, maze->delta.p6.x, maze->delta.p6.y);
		return ;
	} */
	wall_deltas(maze, i);

}


void wall_segment_init(t_maze *maze, int i)
{
	int *seg;

	seg = &maze->segments;
	//we are going to save just the starting point.
	if(maze->w[*seg].st.x == 0)
	{
		maze->w[*seg].st.x = maze->player.ray_x;
		maze->w[*seg].st.y = maze->player.ray_y;
		maze->w[*seg].st.ray = i;
		maze->w[*seg].st.dst = get_wall_dst (&maze->player, maze->w[*seg].st.x, maze->w[*seg].st.y);
	}
	wall_segment(maze, i);
}

void init_wall_segments(t_maze *maze)
{
	int i;

	i = 0;
	maze->segments = 0;
	while (i < W_SEGMENTS)
	{
        maze->w[i].st.x = 0.0;
		maze->w[i].st.y = 0.0;
		maze->w[i].end.x = 0.0;
		maze->w[i].end.y = 0.0;
		i++;
	}
}

void init_wall_delta(t_maze *maze)
{
	ft_memset(&maze->delta, 0, sizeof(t_w_delta));
}

void	touch_points(t_maze *maze, t_player *player)
{
	double	fov;
	double	angle_step;
	int	i;
	double	ray_angle;

	fov = 66 * M_PI / 180; // 66° Rad. Field of View
	//num_rays = 6; // Num of rays
	angle_step = fov / (N_RAYS - 1); // angular increment
	i = 0;
	init_wall_segments(maze);
	while (i <= N_RAYS)
	{
		ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
		player->ray_x = player->x;
		player->ray_y = player->y;
        // Cast the ray
		while (!touch(player->ray_x, player->ray_y, maze))
		{
			player->ray_x += cos(ray_angle); // Move ray in x direction
			player->ray_y += sin(ray_angle); // Move ray in y direction
		}
		wall_segment_init(maze, i);
		//dprintf(maze->fd_log, "%i, %f, %f, %f\n",i, player->ray_x, player->ray_y, get_wall_distance(player));
		i++;
	}
}

void draw_walls(t_maze *maze, t_player *player)
{
	touch_points(maze, player);
	draw_wall_segment(maze);
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
	double	wall_dst;

	fov = 66 * M_PI / 180; // 66° Rad. Field of View
	//num_rays = 6; // Num of rays
	angle_step = fov / (N_RAYS - 1); // angular increment
	fov = 66 * M_PI / 180; // 66° Rad. Field of View
	//num_rays = 6; // Num of rays
	angle_step = fov / (N_RAYS - 1); // angular increment
	i = 0;
	while (i < N_RAYS)
	while (i < N_RAYS)
	{
		ray_angle = player->angle - (fov / 2) + (i * angle_step); // Calculate ray angle
		player->ray_x = player->x;
		player->ray_y = player->y;
		while (!touch(player->ray_x, player->ray_y, maze))
		{
			
			my_pixel_put((int)player->ray_x, (int)player->ray_y, &maze->img_2d, COLOR_YELLOW); // Draw ray pixel
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
	clear_screen(&maze->img_3d);
	clear_screen(&maze->img_2d);
	draw_walls(maze, &maze->player);
	draw_rays(maze, &maze->player);
	draw_map(maze); //Maze is in the back, player is in the front.
	draw_player(maze);
	mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->img_3d.img_ptr, 0, 0);
	mlx_put_image_to_window(maze->mlx_ptr, maze->win_ptr, maze->img_2d.img_ptr, 10, HEIGHT - MAP_SIZE - 10);
	return (0);
}
