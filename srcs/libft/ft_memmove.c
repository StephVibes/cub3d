/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:27:38 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:27:39 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (src == dst)
		return (dst);
	if (src > dst)
	{
		i = 0;
		while (i < len)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			++i;
		}
	}
	else
	{
		i = len - 1;
		while (i != (size_t) - 1)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			--i;
		}
	}
	return (dst);
}

// int main(void)
// {
//   char source[] = "12345123451234512345123";
//   char destination[20];
//   char dest[24];

//   ft_memmove(destination, source, strlen(source) + 1);
//   memmove(dest, source, strlen(source) + 1);

//   printf("Source: %s\n", source);
//   printf("Destination: %s\n", destination);
//   printf("Destination ori: %s\n", dest);
//   return(0);
// }
