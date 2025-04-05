/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:42:15 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 18:21:25 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080
# define N_RAYS 1920
# define MIN_WALL 200
# define MAX_DST 200
# define SPEED 9
# define ANGLE_SPEED 0.08
# define MAP_SIZE 350
# define WALL '1'
# define EMPTY '0'
# define MAX_COLORS 256
# define BLOCK 60
# define FOV 1.151917306316260

# define COLOR_GREEN_1 0x00FFAA00
# define COLOR_RED 0x00FF0000
# define COLOR_GREEN 0x0000FF00
# define COLOR_YELLOW 0x00FFFF00
# define COLOR_BLUE 0x000000FF
# define COLOR_MAGENTA 0x00FF00FF
# define COLOR_CYAN 0x0000FFFF
# define COLOR_WHITE 0x00FFFFFF
# define COLOR_BLACK 0x00000000
# define COLOR_CREAM 0x00F6F2E5   

typedef struct s_flood_fill
{
	char		**map;
	int			**visited;
	int			rows;
	int			cols;

}				t_flood_fill;

typedef struct s_image
{
	void *img_ptr;
	char *data;
	int width;
	int height;
	int bpp;
	int line_len;
	int endian;
}				t_image;

typedef struct s_player
{
	int key_state[4];
	double x;
	double y;
	int			right_rotate;
	int			left_rotate;
	double		angle;
	double		ray_x;
	double		ray_y;
	char		dir;

}				t_player;

typedef struct s_map
{
	char *textures[4];
	t_image *txt_imgs[4];  
	int floor_color_rgb[3];
	int			floor_color;
	int ceiling_color_rgb[3];
	int			ceiling_color;
	char **layout;
	int width;
	int height;
	char player_dir;
	int			block;
	int			offset_2dx;
	int			offset_2dy;
	t_player	mini_player;
}				t_map;

typedef struct s_point
{
	double		x;
	double		y;
	double		dst;
	int			ray;
}				t_point;

typedef struct s_ray
{
	t_point		hit_point;
	int			ray_id;
	double		dst;
	double		angle;
	int			compass[4];
	int			coord;
	double		txt_x;
	double		factor_y;
	double		h;
}				t_ray;

typedef struct s_maze
{
	void		*win_ptr;
	void		*mlx_ptr;
	t_image		img_3d;
	t_image		img_2d;
	int			fd_log;
	t_player	player;
	//double wall_seg[9];
	t_image		screen;
	t_map		*map;
	t_ray		ray[N_RAYS];
	int			show_minimap;
}				t_maze;

// Init
void			maze_init(t_maze *maze);
void			init_textures(t_map *map);

// Main
void			error(char *message);

// Events
int				close_handler(t_maze *maze);
int				key_press_handler(int keycode, t_maze *maze);
int				key_release_handler(int keycode, t_maze *maze);

// Parsing
void			ft_free_split(char **split);
t_map			*load_map(const char *file_name);
void			parse_textures(char **lines, t_map *map);
void			parse_colors(char **lines, t_map *map);
void			parse_map(char **lines, t_map *map);
void			get_player_init_pos(t_maze *maze);
void			get_player_angle(t_maze *maze);
void			get_player_init_pos(t_maze *maze);
void			get_player_init_pos_minimap(t_maze *maze);
void			get_player_angle(t_maze *maze);
void			get_images_xpm(t_map *map, t_maze *maze);
int				is_player(char c);
void			rgb_to_int(t_map *map);
void			free_visited_array(int **visited, int rows);
int				accept_valid(char c);
int				accept_coord(char c);
int				is_map_line(char *line);

// Validation
void			validate_textures(char *textures[]);
int				is_map_closed(char **map, int rows, int cols);
void			validate_map(char **layout, t_map *map);
void			print_debug(t_map *map);
int				is_player(char c);

// Draw
void			my_pixel_put(int x, int y, t_image *img, int color);
void			clear_screen(t_image *screen);
void			move_player(t_player *player);
void			move_player_minimap(t_player *player, int block_map);
void			draw_player(t_maze *maze);
void			draw_wall(t_maze *maze, int i, double ray_angle);
void			draw_utils(t_ray *ray, t_maze *maze);

// Rendering
void			data_init(t_maze *maze);
void			draw_square(t_point *p, int color, t_image *img);
void			maze_render(t_maze *maze);
int				draw_loop(t_maze *maze);
void			draw_map(t_maze *maze);
int				touch(double px, double py, t_maze *maze);
int				touch_minimap(double px, double py, t_maze *maze);
double			perp_wall_dst(t_player *player, double ray_angle);
void			ray_data(t_maze *maze, int i, double ray_angle,
					t_player *player);
void			hit_compass(t_ray *ray, t_maze *maze);
void			def_coord(t_ray *ray, t_maze *maze);
void			draw_ceiling(t_maze *maze, t_ray *ray, double orig_y);
void			draw_floor(t_maze *maze, t_ray *ray, double floor);
void			draw_line(t_maze *maze, t_ray *ray, double orig_y, double yy);
void			draw_rays_minimap(t_maze *maze, t_player *player);
void			draw_rays(t_maze *maze, t_player *player);

// walls
void			wall_segment(t_maze *maze, int i);
void			wall_segment_init(t_maze *maze, int i);
void			init_wall_delta(t_maze *maze);
void			touch_points(t_maze *maze, t_player *player);
void			draw_walls(t_maze *maze, t_player *player);
void			wall_deltas(t_maze *maze, int i);
void			segment_end(t_maze *maze, t_point p);
void			segment_init(t_maze *maze, t_point p);

// textures
void			determine_text(t_ray *ray, t_maze *maze);
void			free_xpm(t_image *img, t_maze *maze);
#endif
