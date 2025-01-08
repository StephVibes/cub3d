/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:30:31 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:30:33 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}

// int main(void)
// {
// char str[] = "Hello, World!";
// char *ptr = ft_strchr(str, 'W');
// printf("Respuesta = %s\n", ptr);

// char str1[] = "Hello, World!";
// char *ptr1 = ft_strchr(str1, 'Z');
// printf("Respuesta = %s\n", ptr1);
// return(0);
// }
