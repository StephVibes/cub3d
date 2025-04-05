/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_closed.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:07:19 by alramire          #+#    #+#             */
/*   Updated: 2025/04/05 16:36:31 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(t_flood_fill *f, int x, int y)
{
	if (x < 0 || y < 0 || x >= f->rows || y >= f->cols)
		return (1);
	if (f->map[x][y] == WALL || f->visited[x][y])
		return (0);
	f->visited[x][y] = 1;
	if (flood_fill(f, x + 1, y) || flood_fill(f, x - 1, y) || 
		flood_fill(f, x, y + 1) || flood_fill(f, x, y - 1))
		return (1);
	else
		return (0);
}

int	**allocate_visited_array(int rows, int cols)
{
	int	**visited;
	int	i;

	visited = (int **)malloc(rows * sizeof(int *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		visited[i] = (int *)calloc(cols, sizeof(int));
		if (!visited[i])
		{
			while (--i >= 0) 
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

int	process_cell(t_flood_fill *f, int i, int j)
{
	if (f->map[i][j] == EMPTY || is_player(f->map[i][j]))
	{
		if (flood_fill(f, i, j))
			return (0);
	}
	return (1);
}

int	check_map_rows(t_flood_fill *f)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	result = 1;
	while (i < f->rows && result)
	{
		j = 0;
		while (j < f->cols)
		{
			if (!process_cell(f, i, j))
			{
				result = 0;
				break ;
			}
			j++;
		}
		i++;
	}
	return (result);
}

int	is_map_closed(char **map, int rows, int cols)
{
	int				result;
	t_flood_fill	f;

	f.map = map;
	f.rows = rows;
	f.cols = cols;
	f.visited = allocate_visited_array(f.rows, f.cols);
	if (!f.visited)
		return (-1);
	result = check_map_rows(&f);
	free_visited_array(f.visited, f.rows);
	return (result);
}
