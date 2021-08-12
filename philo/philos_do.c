/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_do.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niks <niks@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:05:31 by niks              #+#    #+#             */
/*   Updated: 2021/08/12 22:14:22 by niks             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    do_fork(int philo_nb)
{
	timeval time;
	long	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	printf("[%i] Philosopher no. %i has taken a fork.\n",
		ms, philo_nb);
}

void    do_eat(int philo_nb, int eat)
{
	timeval time;
	long	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	printf("[%i] Philosopher no. %i is eating.\n",
		ms, philo_nb);
	usleep(eat);
}

void    do_sleep(int philo_nb, int sleep)
{
	timeval time;
	long	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	printf("[%i] Philosopher no. %i is sleeping.\n",
		ms, philo_nb);
	usleep(sleep);
}

void    do_thonk(int philo_nb)
{
	timeval time;
	long	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	printf("[%i] Philosopher no. %i is thinking.\n",
		ms, philo_nb);
}

void    do_die(int philo_nb)
{
	timeval time;
	long	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	printf("[%i] Philosopher no. %i has died.\n",
		ms, philo_nb);
	exit(1);
}