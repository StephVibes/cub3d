#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
#include <stdbool.h>

# define WIDTH (float)1920
# define HEIGHT (float)1080 
# define N_RAYS 1920
# define MIN_WALL 200
# define MAX_DST 200
# define SPEED 9
# define ANGLE_SPEED 0.08
# define MAP_SIZE 1920
# define WALL '1'
# define EMPTY '0'
# define MAX_COLORS 256

# define COLOR_GREEN_1 0x00FFAA00  // Light green
# define COLOR_RED     0x00FF0000  // Red
# define COLOR_GREEN   0x0000FF00  // Green
# define COLOR_YELLOW  0x00FFFF00  // Yellow
# define COLOR_BLUE    0x000000FF  // Blue
# define COLOR_MAGENTA 0x00FF00FF  // Magenta
# define COLOR_CYAN    0x0000FFFF  // Cyan
# define COLOR_WHITE   0x00FFFFFF  // White
# define COLOR_BLACK   0x00000000  // Black


typedef struct s_image
{
	void	*img_ptr;      // Pointer to the image
	char	*data;		//Pointer to the pixel data
	int 	width;         // Image width
	int		height;        // Image height
	int		bpp;           // Bits per pixel
	int		line_len;   // Length of a line in bytes
	int		endian;        // Endianness
} t_image;


typedef struct s_map {
	char	*textures[4]; // Paths for NO, SO, WE, EA
	t_image	*txt_imgs[4]; // Images of the textures after parsing the xpm files with mlx_xpm_file_to_image()
	int		floor_color_rgb[3]; // RGB for floor color
	int		floor_color;
	int		ceiling_color_rgb[3]; // RGB for ceiling color
	int		ceiling_color;
	char	**layout; // 2D array for the map layout
	int		width; // Width of the map
	int		height; // Height of the map
	char	player_dir; // Initial player direction (N, S, E, W)
	int		block;
	int		offset_2dx;
	int		offset_2dy;
} t_map;

typedef struct s_player
{
	int	key_state[4];    // For tracking key presses WASD
	double	x; // Player's X coordinate
	double	y; // Player's Y coordinate
	int	right_rotate;
	int	left_rotate;
	double	angle;
	double	ray_x;
	double	ray_y;
	char	dir;

} t_player;

typedef struct s_point
{
	double	x;
	double	y;
	double	dst;
	int		ray;
} t_point;

typedef struct s_ray
{
	t_point hit_point;
	int		ray_id;
	double	dst;
	double 	angle;
	int		compass[4];
	int		coord;
	//char 	*txt_path;
	double	txt_x;
	double	factor_y;
	double	h;
} t_ray;

typedef struct s_wall
{
	t_point st;
	t_point end;
	char	delta;
	double	m;
	double	b;

} t_wall;

typedef struct s_wall_delta
{
	t_point p1;
	t_point p2;
	t_point p3;
	t_point p4;
	//t_point p5;
	//t_point p6;
	double	dx1;
	double	dx2;
	double	dx3;
	double	dy1;
	double	dy2;
	double	dy3;

} t_w_delta;

typedef struct s_maze
{
	void		*win_ptr;       // Pointer to the window
	void		*mlx_ptr;       // Pointer to the MLX instance
	t_image		img_3d;         // For rendering the screen buffer
	t_image		img_2d;
	int			fd_log;			//File descriptor, log file.
	t_player	player;         // Player info
	double		wall_seg[9];	// coordinate that defines a wall segment
	t_image		screen;         // For rendering the screen buffer
	t_map		*map;           // Pointer to the map info
	t_ray		ray[N_RAYS];
	int			show_minimap;
} t_maze;

// Init
void	maze_init(t_maze *maze);
void	init_textures(t_map *map);

// Main
void	error(char *message);

//Events
int	close_handler(t_maze *maze);
int	key_press_handler(int keycode, t_maze *maze);
int	key_release_handler(int keycode, t_maze *maze);


// Parsing
void	ft_free_split(char **split);
t_map  	*load_map(const char *file_name);
void	parse_textures(char **lines, t_map *map);
void	parse_colors(char **lines, t_map *map);
void	parse_map(char **lines, t_map *map);
void	get_player_init_pos(t_maze *maze);
void	get_player_angle (t_maze *maze);
void	get_player_init_pos(t_maze *maze);
void	get_player_angle (t_maze *maze);
void	get_images_xpm(t_map *map, t_maze *maze);
int		is_player(char c);
void	rgb_to_int(t_map *map);


// Validation
void	validate_textures(char *textures[]);

// Draw
void     my_pixel_put(int x, int y, t_image *img, int color);
void    clear_screen(t_image *screen);
void    move_player(t_player *player);
void    draw_player(t_maze *maze);

// Rendering
void	draw_square(int x, int y, int size, int color, t_image *screen);
void	maze_render(t_maze *maze);
int		draw_loop(t_maze *maze);
int		draw_loop(t_maze *maze);
void	draw_map(t_maze *maze);
int     touch(double px, double py, t_maze *maze);
double	perp_wall_dst(t_player *player, double ray_angle);
void	ray_data (t_maze *maze, int i, double ray_angle, t_player *player);
void	hit_compass(t_ray *ray, t_maze *maze);
void	def_coord(t_ray *ray, t_maze *maze);
void 	draw_ceiling (t_maze *maze, t_ray *ray, double orig_y);
void	draw_floor (t_maze *maze, t_ray *ray);
void	draw_line (t_maze *maze, t_ray *ray, double orig_y, double yy);

//walls
void	wall_segment(t_maze *maze, int i);
void	wall_segment_init(t_maze *maze, int i);
void 	init_wall_delta(t_maze *maze);
void	touch_points(t_maze *maze, t_player *player);
void	draw_walls(t_maze *maze, t_player *player);
void	wall_deltas(t_maze *maze, int i);
void	segment_end(t_maze *maze, t_point p);
void	segment_init(t_maze *maze, t_point p);

//textures
void	determine_text(t_ray *ray, t_maze *maze);
void	free_xpm(t_image *img, t_maze *maze);
#endif
