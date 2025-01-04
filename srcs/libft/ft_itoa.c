/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:25:08 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:25:11 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int	calc_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	char			*num;
	int				len;

	len = calc_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	num[len] = '\0';
	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	while (len-- > 0)
	{
		num[len] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (n < 0)
		num[0] = '-';
	return (num);
}

// int	main(void)
// {
// 	int test = 12345;
// 	printf("Len de test %d es = %d\n", test, calc_len(test));
// 	printf("str es = %s", ft_itoa(test));
// 	return (0);
// }
