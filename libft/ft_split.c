/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:06:28 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 16:06:32 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static size_t	count_strings(char const *s, char c)
{
	size_t	count;
	int		in_string;

	count = 0;
	in_string = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!in_string)
			{
				count++;
				in_string = 1;
			}
		}
		else
			in_string = 0;
		s++;
	}
	return (count);
}

static void	free_memory(char **array, size_t count)
{
	while (count > 0)
		free(array[--count]);
	free(array);
}

static char	*allocate_string(const char *start, const char *end)
{
	size_t	len;
	size_t	i;
	char	*string;

	len = end - start;
	i = 0;
	string = (char *)malloc(sizeof(char) * (len + 1));
	if (!string)
		return (NULL);
	while (start < end)
		string[i++] = *start++;
	string[i] = '\0';
	return (string);
}

static char	**fill_array(char const *s, char c, char **array,
		size_t string_count)
{
	size_t		str_i;
	const char	*start;

	str_i = 0;
	while (*s && str_i < string_count)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			array[str_i] = allocate_string(start, s);
			if (!array[str_i])
			{
				free_memory(array, str_i);
				return (NULL);
			}
			str_i++;
		}
		else
			s++;
	}
	array[str_i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	string_count;

	string_count = count_strings(s, c);
	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (string_count + 1));
	if (!array)
		return (NULL);
	array = fill_array(s, c, array, string_count);
	return (array);
}
