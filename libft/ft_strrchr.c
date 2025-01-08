/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:23:30 by smanriqu          #+#    #+#             */
/*   Updated: 2023/11/25 22:23:30 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	while (i >= 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
		i--;
	}
	return (NULL);
}

// int main(void)
// {
//   char str[] = "Hello!, World!";
//   char *ptr = ft_strrchr(str, 'o');
//   printf("Respuesta = %s\n", ptr);

//   char str1[] = "Hello, World!";
//   char *ptr1 = ft_strrchr(str1, 'H');
//   printf("Respuesta = %s\n", ptr1);
//   return(0);
// }
