#include "cub3d.h"

void	error()
{
	write(1, "Error usage", 1);
	exit(1);

}

int	main(int argc, char **argv)
{
	t_maze maze;

	if (argc != 2)
		error();
	maze_init(&maze);
	maze_render(&maze);
	mlx_loop();
}

/*int main(void)
{
    void *mlx;
    void *win;
    void *img;
    char *data;
    int bpp, size_line, endian;
    int width = 800, height = 600;

    mlx = mlx_init();
    win = mlx_new_window(mlx, width, height, "Image Example");
    img = mlx_new_image(mlx, width, height);
    data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

    // Fill the image with a gradient
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int color = (x * 255 / width) << 16 | (y * 255 / height) << 8;
            int pixel_pos = (y * size_line) + (x * (bpp / 8));
            *(int *)(data + pixel_pos) = color;
        }
    }

    // Display the image
    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_loop(mlx);
    return 0;
}*/
