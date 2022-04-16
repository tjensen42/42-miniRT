/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:07:47 by hepple            #+#    #+#             */
/*   Updated: 2021/10/21 10:58:15 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function that writes the character 'c' to the file descriptor 'fd'.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
