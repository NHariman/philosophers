/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_forks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 15:32:35 by nhariman      #+#    #+#                 */
/*   Updated: 2021/09/21 18:18:12 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_fork_grabbed(t_philo_id *philo)
{
	long long	wait;
	long long	time;

	wait = 0;
	pthread_mutex_lock(&philo->stats->print_lock);
	time = elapsed_time(philo->stats->start_time);
	printf("[%lld] Philosopher %lld has taken up cutlery\n",
		time, philo->id);
	pthread_mutex_unlock(&philo->stats->print_lock);
	return (1);
}

static int	grab_multi(t_philo_id *philo)
{
	int	stick[2];

	stick[0] = 0;
	stick[1] = 0;
	while (stick[0] != 1 || stick[1] != 1)
	{
		if (philo->id == 0 && stick[0] != 1)
		{
			philo_lock(
				&philo->stats->lock[philo->stats->num_philos - 1], &stick[0]);
		}
		else if (philo->id == philo->stats->num_philos - 1 && stick[1] != 1)
			philo_lock(&philo->stats->lock[0], &stick[1]);
		else if (philo->id >= 0 && philo->id < philo->stats->num_philos - 1
			&& stick[1] != 1)
			philo_lock(&philo->stats->lock[philo->id], &stick[1]);
		else if (philo->id > 0
			&& philo->id <= philo->stats->num_philos - 1 && stick[0] != 1)
			philo_lock(&philo->stats->lock[philo->id - 1], &stick[0]);
	}
	return (1);
}

int	grab_fork(t_philo_id *philo)
{
	if (philo->stats->num_philos != 1)
	{
		if (grab_multi(philo))
			return (print_fork_grabbed(philo));
		return (0);
	}
	else
	{
		if (!pthread_mutex_lock(&philo->stats->lock[philo->id]))
			return (print_fork_grabbed(philo));
		return (0);
	}
}

static int	put_down_multi(t_philo_id *philo)
{
	if (philo->id == 0)
		pthread_mutex_unlock(
			&philo->stats->lock[philo->stats->num_philos - 1]);
	if (philo->id >= 0 && philo->id < philo->stats->num_philos - 1)
		pthread_mutex_unlock(&philo->stats->lock[philo->id]);
	if (philo->id == philo->stats->num_philos - 1)
		pthread_mutex_unlock(&philo->stats->lock[0]);
	if (philo->id > 0 && philo->id <= philo->stats->num_philos - 1)
		pthread_mutex_unlock(&philo->stats->lock[philo->id - 1]);
	return (1);
}

int	put_down_fork(t_philo_id *philo)
{
	if (philo->stats->num_philos != 1)
	{
		if (put_down_multi(philo))
			return (1);
		return (0);
	}
	else
	{
		if (!pthread_mutex_unlock(&philo->stats->lock[philo->id]))
			return (1);
		return (0);
	}
}
