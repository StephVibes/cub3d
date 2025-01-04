/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 22:23:48 by smanriqu          #+#    #+#             */
/*   Updated: 2023/11/25 22:23:48 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		return (c - 32);
	return (c);
}

// int main (void)
// {
//   printf("return (value of a = %d\n", ft_toupper('a')));
//   printf("return (value of B = %d\n", ft_toupper('B')));
//   printf("return (value of $ = %d\n", ft_toupper('$')));
//   char a  = ft_toupper('a');
//   write(1, &a, 1);
//   char b  = ft_toupper('B');
//   write(1, &b, 1);
//   char c  = ft_toupper('$');
//   write(1, &c, 1);

//   printf("-------\nreturn (value of a = %d\n", toupper('a')));
//   printf("return (value of B = %d\n", toupper('B')));
//   printf("return (value of $ = %d\n", toupper('$')));
//   return(0);
// }
