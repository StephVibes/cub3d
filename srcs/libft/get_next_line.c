#include "libft.h"

static char	*find_nl(const char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return ((char *)s);
		s++;
	}
	if (*s == '\n')
		return ((char *)s);
	else
		return (NULL);
}

static void	*handling_newline(char **line, char **buffer)
{
	char	*temp;
	char	*new_line;
	size_t	new_size;

	if (buffer == NULL || *buffer == NULL)
		return (NULL);
	if (find_nl(*buffer))
	{
		temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!temp)
			return (free(temp), NULL);
		new_line = find_nl(*buffer) + 1;
		ft_strlcpy(temp, *buffer, ((new_line) - *buffer));
		*line = ft_strjoin(*line, temp);
		new_size = ft_strlen(new_line);
		ft_strlcpy(temp, new_line, new_size);
		free(*buffer);
		*buffer = temp;
		return (*buffer);
	}
	else
		return (NULL);
}

static int	reading(int fd, char **line, char *buffer, int *bytes_read)
{
	*line = ft_gnl_strjoin(*line, buffer);
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[*bytes_read] = '\0';
	if ((*bytes_read <= 0 && *line[0] == '\0') || (*bytes_read == 0
			&& *line[0] == !'\0'))
	{
		free(*line);
		return (1);
	}
	return (0);
}

static void	*error_and_line_init(int fd, char **buffer, char **line)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		*buffer = freeing(*buffer, NULL);
		return (NULL);
	}
	*line = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!*line)
	{
		*buffer = freeing(*buffer, NULL);
		return (free(*line), NULL);
	}
	return (*buffer);
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	static char	*buffer;
	char		*line;

	line = NULL;
	bytes_read = 1;
	if (!buffer)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!buffer)
			return (free(buffer), NULL);
	}
	if (!error_and_line_init(fd, &buffer, &line))
		return (free(line), NULL);
	while (bytes_read > 0)
	{
		if (handling_newline(&line, &buffer))
			break ;
		if (reading(fd, &line, buffer, &bytes_read))
		{
			buffer = freeing(buffer, NULL);
			return (NULL);
		}
	}
	return (line);
}
