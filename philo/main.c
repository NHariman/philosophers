/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/27 21:29:04 by nhariman      #+#    #+#                 */
/*   Updated: 2021/07/27 22:05:00 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_invalid_input(void)
{
	ft_putstr_fd("Invalid amount of arguments\n", 2);
	ft_putstr_fd("Please provide the following arguments:\n", 2);
	ft_putstr_fd(
		"-[number_of_philosophers]\n-[time_to_die] in milliseconds\n", 2);
	ft_putstr_fd("-[time_to_eat] in milliseconds\n", 2);
	ft_putstr_fd("-[time_to_sleep] in milliseconds\n", 2);
	ft_putstr_fd("-[number_of_times_each_philosopher_must_eat] Optional\n", 2);
	return (1);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 6 && argc != 5)
		return (ft_invalid_input());
	return (0);
}
