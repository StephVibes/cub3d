#include "libft.h"

char	*f_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (*s != (char)c)
		return (NULL);
	return (s);
}

char	*f_strdup(char *s1)
{
	char	*copy;
	int		i;

	i = 0;
	copy = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*f_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	if (s1 == NULL)
		return (f_strdup(s2));
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}

int	ft_malloc_count(char *stock)
{
	int	i;

	i = 0;
	if (f_strchr(stock, '\n') == NULL)
		return (ft_strlen(stock));
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	return (i + 1);
}

char	*ft_get_the_line(char *stock)
{
	char	*line;
	int		i;
	int		len;

	line = NULL;
	len = ft_malloc_count(stock);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] && i < len)
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	ft_get_the_spare(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	i = i + 1;
	j = 0;
	while (i < BUFFER_SIZE)
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
}

char	*ft_line_results(int ret, char *stock, char *buffer)
{
	char		*line;

	line = NULL;
	if (ft_strlen(stock) == 0)
	{
		free(stock);
		return (NULL);
	}
	line = ft_get_the_line(stock);
	if (ret > 0)
		ft_get_the_spare(buffer);
	free(stock);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*stock;
	int			ret;

	stock = NULL;
	if ((read(fd, buffer, 0) == -1) || BUFFER_SIZE <= 0)
		return (NULL);
	ret = 1;
	stock = f_strjoin(stock, buffer);
	while (f_strchr(stock, '\n') == NULL && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
		{
			free(stock);
			return (NULL);
		}
		buffer[ret] = '\0';
		stock = f_strjoin(stock, buffer);
	}
	return (ft_line_results(ret, stock, buffer));
}
