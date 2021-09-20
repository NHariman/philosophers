/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_forks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 15:32:35 by nhariman      #+#    #+#                 */
/*   Updated: 2021/09/20 18:33:09 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	put_down_multi(t_philo_id *philo)
{
	if (philo->id >= 0 && philo->id < philo->stats->num_philos - 1
		&& !pthread_mutex_unlock(&philo->stats->lock[philo->id + 1]))
		return (1);
	else if (philo->id == 0
		&& !pthread_mutex_unlock(
			&philo->stats->lock[philo->stats->num_philos - 1]))
		return (1);
	else if (philo->id == philo->stats->num_philos - 1
		&& !pthread_mutex_unlock(&philo->stats->lock[0]))
		return (1);
	else if (philo->id > 0 && philo->id <= philo->stats->num_philos - 1
		&& !pthread_mutex_unlock(&philo->stats->lock[philo->id - 1]))
		return (1);
	else
		return (0);
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

static int	grab_multi(t_philo_id *philo)
{
	if (philo->id >= 0 && philo->id < philo->stats->num_philos - 1
		&& !pthread_mutex_lock(&philo->stats->lock[philo->id + 1]))
		return (1);
	else if (philo->id == 0
		&& !pthread_mutex_lock(
			&philo->stats->lock[philo->stats->num_philos - 1]))
		return (1);
	else if (philo->id == philo->stats->num_philos - 1
		&& !pthread_mutex_lock(&philo->stats->lock[0]))
		return (1);
	else if (philo->id > 0
		&& philo->id <= philo->stats->num_philos - 1
		&& !pthread_mutex_lock(&philo->stats->lock[philo->id - 1]))
		return (1);
	else
		return (0);
}

int	grab_fork(t_philo_id *philo)
{
	long long	time;

	time = elapsed_time(philo->stats->start_time);
	if (philo->stats->num_philos != 1)
	{
		if (grab_multi(philo))
			return (
				printf(
					"[%lld] Philosopher %lld has taken a fork.\n",
					time, philo->id));
		return (0);
	}
	else
	{
		if (!pthread_mutex_lock(&philo->stats->lock[philo->id]))
			return (
				printf(
					"[%lld] Philosopher %lld has taken a fork.\n",
					time, philo->id));
		return (0);
	}
}
