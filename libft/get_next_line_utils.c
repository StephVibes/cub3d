/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:31:50 by smanriqu          #+#    #+#             */
/*   Updated: 2025/04/10 11:34:09 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
