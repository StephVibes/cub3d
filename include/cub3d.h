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

# define WIDTH 1200
# define HEIGHT 800
# define N_RAYS 300
# define MIN_WALL 200
# define MAX_DST 200
# define W_SEGMENTS 100
# define SPEED 1
# define ANGLE_SPEED 0.01
# define MAP_SIZE 290

# define COLOR_GREEN_1 0x00FFAA00  // Light green
# define COLOR_RED     0x00FF0000  // Red
# define COLOR_GREEN   0x0000FF00  // Green
# define COLOR_YELLOW  0x00FFFF00  // Yellow
# define COLOR_BLUE    0x000000FF  // Blue
# define COLOR_MAGENTA 0x00FF00FF  // Magenta
# define COLOR_CYAN    0x0000FFFF  // Cyan
# define COLOR_WHITE   0x00FFFFFF  // White



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
	int		floor_color[3]; // RGB for floor color
	int		ceiling_color[3]; // RGB for ceiling color
	char	**layout; // 2D array for the map layout
	int		width; // Width of the map
	int		height; // Height of the map
	char	player_dir; // Initial player direction (N, S, E, W)
	double	block;
	int	offset_2dx;
	int	offset_2dy;
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
	void		*mlx_ptr;       // Pointer to the MLX instance
	void		*win_ptr;       // Pointer to the window
	//t_image		textures[4];     // Array for wall textures (e.g., north, south, east, west)
	t_image		img_3d;         // For rendering the screen buffer
	t_image		img_2d;
//	double		plane_x;        // Camera plane X
//	double		plane_y;        // Camera plane Y
	t_map		*map;           // Pointer to the map info
	int			fd_log;			//File descriptor, log file.
	t_player	player;         // Player info
	//double		wall_seg[9];	// coordinate that defines a wall segment
	t_wall		w[W_SEGMENTS];
	t_w_delta	delta;
	int			segments;
} t_maze;

// Init
void	maze_init(t_maze *maze);

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
void	draw_map(t_maze *maze);
int     touch(double px, double py, t_maze *maze);

//walls
void	wall_segment(t_maze *maze, int i);
void	wall_segment_init(t_maze *maze, int i);
void 	init_wall_delta(t_maze *maze);
void	touch_points(t_maze *maze, t_player *player);
void	draw_walls(t_maze *maze, t_player *player);
void	wall_deltas(t_maze *maze, int i);
void	segment_end(t_maze *maze, t_point p);
void	segment_init(t_maze *maze, t_point p);
#endif
