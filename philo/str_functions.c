/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/27 21:30:36 by nhariman      #+#    #+#                 */
/*   Updated: 2021/07/27 21:47:12 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		write(fd, "(null)", 6);
	else
		write(fd, str, ft_strlen(str));
}
