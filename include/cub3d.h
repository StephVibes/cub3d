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
# define SQUARE 35
# define N_RAYS 300
# define MIN_WALL 200
# define MAX_DST 200

typedef struct s_image
{
	void	*img_ptr;      // Pointer to the image
	char	*data;         // Pointer to the pixel data
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
	int		map_width; // Width of the map
	int		map_height; // Height of the map
	char	player_dir; // Initial player direction (N, S, E, W)
//	int		player_x; // Player's starting X coordinate
//	int		player_y; // Player's starting Y coordinate
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

typedef struct s_maze
{
	void		*mlx_ptr;        // Pointer to the MLX instance
	void		*win_ptr;        // Pointer to the window
	//t_image		textures[4];     // Array for wall textures (e.g., north, south, east, west)
	t_image		screen;          // For rendering the screen buffer
//	double		plane_x;         // Camera plane X
//	double		plane_y;         // Camera plane Y
	t_map		*map;            // Pointer to the map info

	t_player	player;          // Player info
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

// Rendering

void	draw_square(int x, int y, int size, int color, t_image *screen);
void	maze_render(t_maze *maze);
int		draw_loop(t_maze *maze);
void	draw_map(t_maze *maze);
int     touch(double px, double py, t_maze *maze);

#endif
