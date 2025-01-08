/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:23:39 by smanriqu          #+#    #+#             */
/*   Updated: 2023/11/25 22:23:39 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		return (c + 32);
	return (c);
}

// int main (void)
// {
//   printf("return (value of a = %d\n", ft_tolower('a')));
//   printf("return (value of B = %d\n", ft_tolower('B')));
//   printf("return (value of $ = %d\n", ft_tolower('$')));
//   char a  = ft_tolower('a');
//   write(1, &a, 1);
//   char b  = ft_tolower('B');
//   write(1, &b, 1);
//   char c  = ft_tolower('$');
//   write(1, &c, 1);

//   printf("-------\nreturn (value of a = %d\n", tolower('a')));
//   printf("return (value of B = %d\n", tolower('B')));
//   printf("return (value of $ = %d\n", tolower('$')));
//   return(0);
// }
