/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niks <niks@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 21:30:36 by nhariman          #+#    #+#             */
/*   Updated: 2021/08/10 00:41:51 by niks             ###   ########.fr       */
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
	write(fd, str, ft_strlen(str));
}

/*
** custom atoll that only looks for positive values.
** if a negative value is detected the program exits with -1
** this can be caught by the function that fills the philo struct
** which then knows the input is invalid.
*/

long long	ft_atoll(const char *nptr)
{
	long long	result;
	long long	i;

	result = 0;
	i = 0;
	while (is_space(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			return (-1);
		i++;
	}
	while (nptr[i] != '\0')
	{
		if (!is_digit(nptr[i]))
			return (-1);
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result);
}
