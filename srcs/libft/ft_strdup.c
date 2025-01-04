/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:43:24 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:43:28 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1) + 1;
	i = 0;
	ptr = (char *)malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < len && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int main() {
//     const char *original = "Hello, world!";
//     char *duplicate;

//     duplicate = ft_strdup(original);

//     printf("Original string: %s\n", original);
//     printf("Duplicated string: %s\n", duplicate);
//     free(duplicate);
//     return (0);
// }
