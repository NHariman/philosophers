/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 14:58:00 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/29 20:11:02 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec) * 1000) + ((time.tv_usec) / 1000));
}

long long	elapsed_time(long long start_time)
{
	long long	current_time;

	current_time = get_time();
	return (current_time - start_time);
}

void	mr_sandman(unsigned long ms)
{
	unsigned long	time;

	time = get_time();
	while ((get_time() - time) < ms)
		usleep(100);
}
