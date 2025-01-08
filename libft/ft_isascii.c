/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:23:56 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:24:00 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_isascii(int c)
{
	if (c > -1 && c < 128)
		return (1);
	return (0);
}

// int	main(void)
// {
// 	int result = ft_isascii('5');
//   printf("%d\n", result);
//   return(0);
// }
