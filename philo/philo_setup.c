/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:24:04 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/04 19:40:24 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_vars(t_philo_id *philo, t_gen_stats stats, long long i)
{
	philo->id = i;
	philo->last_meal = 0;
	philo->stats = &stats;
	philo->death = false;
}

// join threads function here
static int	join_threads(t_philo_id *philo, long long nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_join(philo[i]->tid, NULL);
		i++;
	}
	free(philo);
	return (0);
}

// create threads function here
static int	create_threads(t_philo_id *philo,
		t_gen_stats *stats, long long num_philos)
{
	pthread_t	monitor;
	int			error;
	long long	i;

	i = 0;
	error = pthread_create(monitor, NULL, &monitoring_system, (void *)stats);
	if (error)
		return (1);
	philo = (t_philo_id *)malloc(num_philos * sizeof(t_philo_id));
	if (!philo)
		return (end_monitoring(&stats));
	while (i < num_philos)
	{
		init_philo_vars(&philo[i], stats, i);
		error = pthread_create(
				&philo[i]->tid, NULL, &live_your_life, (void *)philo);
		if (error)
			return (join_threads(philo, i));
		usleep(5000);
		i++;
	}
	return (0);
}

int	setup_philos(t_gen_stats *stats)
{
	t_philo_id	*philo;

	if (initialise_mutex_locks(stats) != 0)
		return (1);
	if (create_threads(philo, stats, stats->num_philos))
		return (1);
	join_threads(philo, stats->num_philos);
	destroy_mutex_locks(stats);
	return (0);
}
