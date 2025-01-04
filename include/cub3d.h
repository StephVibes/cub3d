#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1200
# define HEIGHT 900

typedef struct s_image
{
    void    *img_ptr;      // Pointer to the image
    char    *data;         // Pointer to the pixel data
    int     width;         // Image width
    int     height;        // Image height
    int     bpp;           // Bits per pixel
    int     line_length;   // Length of a line in bytes
    int     endian;        // Endianness
} t_image;

typedef struct s_maze
{
    void        *mlx_ptr;        // Pointer to the MLX instance
    void        *win_ptr;        // Pointer to the window
    t_image     textures[4];     // Array for wall textures (e.g., north, south, east, west)
    t_image     screen;          // For rendering the screen buffer
    double      player_x;        // Player's X position
    double      player_y;        // Player's Y position
    double      dir_x;           // Player's direction X
    double      dir_y;           // Player's direction Y
    double      plane_x;         // Camera plane X
    double      plane_y;         // Camera plane Y
    char        **map;           // 2D array representing the map
    int         map_width;       // Map width
    int         map_height;      // Map height
    int         key_state[256];  // For tracking key presses
} t_maze;


#endif
