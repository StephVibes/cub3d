/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:22:40 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:22:43 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t n)
{
	void	*ptr;

	if (count == 0 || n == 0)
		return (malloc(0));
	ptr = malloc(count * n);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * n);
	return (ptr);
}

// int main() {
//     int* arr;
//     size_t num_elements = 5;
//     size_t element_size = sizeof(int);

//     arr = (int*)ft_calloc(num_elements, element_size);

//     if (arr != NULL) {
//         printf("Memory allocated successfully using ft_calloc:\n");
//         size_t i = 0;
//         while (i < num_elements) {
//             printf("%d ", arr[i]);
//             i++;
//         }
//         free(arr);
//     } else {
//         printf("Memory allocation failed\n");
//     }

//     return (0);
// }
