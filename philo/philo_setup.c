/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:24:04 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/18 20:52:28 by nhariman      ########   odam.nl         */
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

static int	init_philo_lifecycle(t_philo_id *philo, t_gen_stats *stat,
			long long num_philos)
{
	long long	i;
	int			error;

	i = 0;
	error = 0;
	while (i < num_philos)
	{
		init_philo_vars(&philo[i], stat, i);
		error = pthread_create(
				&philo[i].tid, NULL, &live_your_life, (void *)&philo[i]);
		if (error)
			return (1);
		pthread_detach(philo[i].tid);
		usleep(1000);
		i++;
	}
	return (0);
}

// create threads function here
static int	create_threads(t_gen_stats *stats, long long num_philos)
{
	t_philo_id	*philo;
	pthread_t	monitor;
	int			error;
	long long	i;

	i = 0;
	monitor = NULL;
	error = pthread_create(&monitor, NULL, &monitoring_system, (void *)stats);
	if (error)
		return (1);
	philo = (t_philo_id *)malloc(num_philos * sizeof(t_philo_id));
	if (!philo)
		return (end_monitoring(stats, &monitor));
	error = init_philo_lifecycle(philo, stats, num_philos);
	if (error)
		end_monitoring(stats, &monitor);
	else
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
