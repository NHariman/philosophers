/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos_do.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 17:05:31 by niks          #+#    #+#                 */
/*   Updated: 2021/09/21 12:34:58 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_living(t_philo_id *philo, int status)
{
	if (philo->stats->death_occured)
		return ;
	if (status == eat)
	{
		printf("is eating\n");
		usleep(philo->stats->eat * 1000);
		philo->last_meal = elapsed_time(philo->stats->start_time);
		put_down_fork(philo);
	}
	else if (status == sleepy)
	{
		printf("is sleeping\n");
		usleep(philo->stats->sleep * 1000);
	}
	else if (status == think)
		printf("is thinking\n");
}

void	philo_action(t_philo_id *philo, int status)
{
	long long	time;

	if (philo->stats->death_occured)
		return ;
	time = elapsed_time(philo->stats->start_time);
	printf("[%lld] Philosopher %lli ", time, philo->id);
	if (time - philo->last_meal > philo->stats->die)
	{
		philo->death = true;
		philo->stats->death_occured = true;
		printf("has died\n");
		return ;
	}
	else
		philo_living(philo, status);
}
