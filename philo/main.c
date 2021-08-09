/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niks <niks@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 21:29:04 by nhariman          #+#    #+#             */
/*   Updated: 2021/08/10 00:47:24 by niks             ###   ########.fr       */
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

static int	ft_invalid_number(void)
{
	ft_putstr_fd("Invalid Number.\nDo not use negative numbers or input anything that isn't just digits 0-9.\n", 2);
	return (0);
}

static int	ft_fill_stats(t_philo_stats *stats, char **av, int ac)
{
	stats->philos = ft_atoll(av[1]);
	stats->die = ft_atoll(av[2]);
	stats->eat = ft_atoll(av[3]);
	stats->sleep = ft_atoll(av[4]);
	if (ac == 6)
		stats->must_eat = ft_atoll(av[5]);
	else
		stats->must_eat = -2;
	if (is_negative(stats->philos) || is_negative(stats->die) ||
	is_negative(stats->eat) || is_negative(stats->sleep) ||
	(ac == 6 && is_negative(stats->must_eat)))
		return (ft_invalid_number());
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo_stats stats;

	if (argc != 6 && argc != 5)
		return (ft_invalid_input());
	if (!ft_fill_stats(&stats, argv, argc))
		return (1);
	return (0);
}
