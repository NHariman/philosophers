/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:24:04 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/08 17:46:11 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo_vars(t_philo_id *philo, t_gen_stats *stats, long long i)
{
	philo->id = i;
	philo->last_meal = 0;
	philo->stats = stats;
	philo->death = false;
}

// create threads function here
static int	create_threads(t_gen_stats *stats, long long num_philos)
{
	t_philo_id	*philo;
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
				&philo[i].tid, NULL, &live_your_life, (void *)&philo[i]);
		if (error)
			return (join_threads(philo, i));
		pthread_detatch(philo[i].tid);
		usleep(1000);
		i++;
	}
	pthread_join(monitor, NULL);
	free(philo);
	return (0);
}

int	setup_philos(t_gen_stats *stats)
{
	if (initialise_mutex_locks(stats) != 0)
		return (1);
	if (create_threads(stats, stats->num_philos))
		return (1);
	destroy_mutex_locks(stats);
	return (0);
}
