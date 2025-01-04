/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:27:57 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:28:00 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	value;
	size_t			i;

	ptr = b;
	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		ptr[i] = value;
		i++;
	}
	return (ptr);
}

// int	main(void)
// {
// 	char test1[7];
// 	char test2[7];
// 	size_t len = sizeof(test1) - 1;
// 	printf("Mi resultado:%s\n", ft_memset(test1, 'A', len));
// 	printf("Resultado funcion original:%s\n", memset(test2, 'A', len));
// 	printf("%zu\n", len);
// 	return (0);
// }
