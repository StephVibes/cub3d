/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:45:18 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:45:20 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>
#include <stdio.h>
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	i;
	size_t	j;

	dst_len = ft_strlen(dst);
	i = dst_len;
	j = 0;
	if (dstsize <= dst_len)
		return (dstsize + ft_strlen(src));
	while (src[j] && i < dstsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst_len + ft_strlen(src));
}

// int main(void)
// {
//   char *str = "the cake is a lie !\0I'm hidden lol\r\n";
//   char buff1[0xF00] = "there is no stars in the sky";
//   char buff2[0xF00] = "there is no stars in the sky";
//   size_t max = strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4;

//   printf("My function return (value = %lu\n", ft_strlcat(buff2, str, max)));
//   printf("My function dst string= %s\n ------ \n", buff2);
//   printf("Original function dst string= %s\n ------ \n", buff1);
//   return(0);
// }
