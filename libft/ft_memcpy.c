/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:45:00 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:45:03 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((const char *)src)[i];
		i++;
	}
	return (dst);
}

// int main(void)
// {
//   char source[] = "12345123451234512345123";
//   char destination[20];
//   char dest[24];

//   //printf("size: %zu\n", sizeof(destination));
//   ft_memcpy(((void*)0), "segfaulter tu dois", 17);
//   memcpy(((void*)0), "segfaulter tu dois", 17);

//   printf("Source: %s\n", source);
//   printf("Destination: %s\n", destination);
//   printf("size: %zu\n", sizeof(destination));
//   printf("Destination ori: %s\n", dest);
//   return(0);
// }
