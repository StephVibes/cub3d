#include "cub3d.h"

void get_player_init_pos(t_maze *maze)
{
	int i;
	int j;

	i = 0;
	

	while(i < maze->map->map_height)
	{
		j = 0;
		while(j < maze->map->map_width)
		{
			if(maze->map->layout[i][j] != '0' && maze->map->layout[i][j] != '1')
				{
					maze->player.x = j * SQUARE;
					maze->player.y = i * SQUARE;
					maze->player.dir = maze->map->layout[i][j];
					return;
				}
			j++;
		}
		i++;
	}

}

void get_player_angle (t_maze *maze)
{
	if(maze->player.dir == 'N')
		maze->player.angle = (3 * M_PI) / 2;
	else if (maze->player.dir == 'S')
		maze->player.angle = M_PI / 2;
	else if (maze->player.dir == 'E')
		maze->player.angle = 2 * M_PI;
	else if (maze->player.dir == 'W')
		maze->player.angle = M_PI;
}
