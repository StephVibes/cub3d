/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:42:24 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:42:27 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			i;
	unsigned int	src_len;

	src_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > src_len)
		len = 0;
	else if (len > (src_len - start))
		len = src_len - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int main() {
//     const char *original = "Hello, world!";
//     int start_index = 7;
//     int length = 5;

//     // Test the substr function
//     char *substring = ft_substr(original, start_index, length);

//     if (substring != NULL) {
//         printf("Original string: %s\n", original);

	//         free(substring);
	//     }

	//     return (0);
	// }
