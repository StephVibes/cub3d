/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:23:07 by smanriqu          #+#    #+#             */
/*   Updated: 2023/11/25 22:23:07 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && n > 1)
	{
		s1++;
		s2++;
		n--;
	}
	return (((unsigned char)(*s1) - (unsigned char)(*s2)));
}
// int main()
// {
// 	char s1[] = "";
// 	char s2[] = "";
// 	unsigned int n = 17;
// 	printf("strncmp function result = %d\n", strncmp(s1, s2, n));
// 	printf("ft_strncmp function result = %d\n", ft_strncmp(s1, s2, n));
// 	return (0);
// }
