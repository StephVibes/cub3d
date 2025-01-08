/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:34:38 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:34:39 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	len;
	int		i;

	len = ft_strlen(s);
	i = 0;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// char	uppercase(unsigned int i, char c)
// {
// 	if (i % 2 == 0)
// 		return (toupper(c));
// 	else
// 		return (tolower(c));
// }

// int	main(void)
// {
// 	printf("%s", ft_strmapi("Hello, World!", uppercase));
// 	return (0);
// }
