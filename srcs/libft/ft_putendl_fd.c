/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanriqu <smanriqu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:28:45 by smanriqu          #+#    #+#             */
/*   Updated: 2023/12/05 14:28:47 by smanriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_putchar_fd(char c, int fd);

void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
		ft_putchar_fd(*s++, fd);
	ft_putchar_fd(10, fd);
}
