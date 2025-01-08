#include "libft.h"

void	*freeing(char *buffer, char *line)
{
	free(buffer);
	free(line);
	buffer = NULL;
	return (NULL);
}

char	*ft_gnl_strjoin(char *s1, char const *s2)
{
	char	*ptr;
	size_t	len;
	size_t	i;
	size_t	j;
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	len = len_s1 + ft_strlen(s2);
	i = 0;
	ptr = ft_calloc((len + 1), 1);
	if (!ptr)
		return (free(ptr), NULL);
	while (i < len_s1 && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < len && s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (free(s1), ptr);
}
