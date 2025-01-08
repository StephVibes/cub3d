/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:26:00 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:26:02 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		chr;
	const unsigned char	*ptr;

	chr = c;
	ptr = s;
	while (n--)
	{
		if (*ptr == chr)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}

// int main (void)
// {
// 	char test[] = "This is a test string for ft_memchr function";
// 	printf("My function ptr = %p\n", ft_memchr(test, 'T', 5));
// 	printf("Original function ptr = %p\n", memchr(test, 'T', 5));
// 	return(0);
// }
