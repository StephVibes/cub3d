/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:33:35 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:33:38 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <bsd/string.h>
#include <stdio.h>
#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*(src + i))
		i++;
	if (!dstsize)
		return (i);
	while (--dstsize && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (i);
}
// int main(void)
// {
//         char src[] = "Hola, esto es una prueba";
//         char dest[10];
//         printf("strlcpy function result = %zu\n",
// 		strlcpy(dest, src, sizeof(dest)));
//         printf("ft_strlcpy function result = %zu\n",
// 		ft_strlcpy(dest, src, sizeof(dest)));
//         printf("destination = %s\n", dest);
// 	return (0);
// }
