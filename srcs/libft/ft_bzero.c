/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:22:20 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:22:25 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

/*int main(void)
{
  char test1[] = "Hola";
  char test2[] = "Hola";
  size_t len = sizeof(test1) -1;
  ft_bzero(test1, len);
  bzero(test2, len);
  printf("Mi resultado:%s\n", test1);
  printf("Resultado funcion original:%s\n", test2);
  printf("%zu\n", len);
  return(0);
}*/
