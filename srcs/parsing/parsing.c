#include "cub3d.h"

static int	count_lines(char *file_name)
{
	int	fd;
	char	*line;
	int	num_lines;

	num_lines = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error(); // improve
	line = get_next_line(fd);
	while (line != NULL)
	{
		num_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return(num_lines);
}

char	**read_file(char *file_name)
{
	int	num_lines;
	int	fd;
	char	**lines;

	num_lines = count_lines(file_name);
	lines = malloc(num_lines * sizeof(char *));

	fd = open(file_name);
	//duplicar cada linea al nuevo malloc
	close(fd)
}
