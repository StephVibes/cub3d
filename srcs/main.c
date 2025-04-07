/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:07:57 by alramire          #+#    #+#             */
/*   Updated: 2025/04/07 12:18:52 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
}

int	parsing(char *map_name, t_maze *maze)
{
	maze->map = load_map(map_name);
	if (!maze->map)
		return (1);
	else
		return (0);
}

int	main(int argc, char **argv)
{
	t_maze	maze;

	if (argc != 2)
		error("Not enough arguments");
	if (parsing(argv[1], &maze) != 0)
		error("Error parsing map");
	maze_init(&maze);
	maze.fd_log = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (maze.fd_log == -1)
		error("Failed to open log file");
	mlx_loop_hook(maze.mlx_ptr, draw_loop, &maze);
	mlx_loop(maze.mlx_ptr);
	if (maze.fd_log > 0)
		close(maze.fd_log);
	return (0);
}
