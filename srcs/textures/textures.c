#include "cub3d.h"

double reescale(int value, int block) {
    double	new;

	if (block == 0)
		return (0.0);
	new = (double)value / (double)block;
	return (new);
}

double get_text_x(double val, int txt_width)
{
	double	text_x;

    if (val < 0.0)
        val = 0.0;
    if (val > 1.0)
        val = 1.0;
    text_x = floor(val * ( txt_width - 1));
	return (text_x);
}

void	determine_text(t_ray *ray, t_maze *maze)
{
	double	mod; // Value 
	double	val;

	if (ray->coord == 0 || ray->coord == 1)
		mod = ((int)ray->hit_point.x - maze->map->offset_2dx) % maze->map->block;
	else
		mod = ((int)ray->hit_point.x - maze->map->offset_2dy) % maze->map->block;
	val = reescale(mod, maze->map->block);
	ray->txt_x = get_text_x(val, maze->map->txt_imgs[ray->coord]->width); // According to the type of texture we get the width of the parsed xpm
}
