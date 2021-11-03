/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:24:04 by nhariman      #+#    #+#                 */
/*   Updated: 2021/11/03 21:52:58 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo_vars(t_philo_id *philo, t_gen_stats *stats, long long i)
{
	philo->id = i;
	philo->last_meal = 0;
	philo->meal_count = 0;
	philo->stats = stats;
	philo->death = false;
	if (pthread_mutex_init(&philo->eat_lock, NULL) != 0)
		return (ft_prnt_err("Error\nMutex init failure.\n"));
	return (0);
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
		if (init_philo_vars(&philo[i], stat, i))
			return (1);
		error = pthread_create(
				&philo[i].tid, NULL, &live_your_life, (void *)&philo[i]);
		if (error)
			return (1);
		usleep(1000);
		i++;
	}
	return (0);
}

static void	join_philo_threads(t_philo_id *philo, long long num_philos)
{
	long long	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
}

// create threads function here
static int	create_threads(t_gen_stats *stats, long long num_philos)
{
	t_philo_id	*philo;

	philo = (t_philo_id *)malloc(num_philos * sizeof(t_philo_id));
	if (!philo)
		return (1);
	init_philo_lifecycle(philo, stats, num_philos);
	join_philo_threads(philo, num_philos);
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
