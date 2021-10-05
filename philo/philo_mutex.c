/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_mutex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:47:47 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/05 16:18:21 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// initialise mutex locks here
int	initialise_mutex_locks(t_gen_stats *stats)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&stats->print_lock, NULL) != 0)
		return (ft_prnt_err("Error\nMutex init failure.\n"));
	stats->locks = (pthread_mutex_t *)malloc(
			(pthread_mutex_t)stats->num_philos);
	while (i < stats->num_philos)
	{
		if (pthread_mutex_init(&stats->lock[i], NULL) != 0)
		{
			free(stats->lock);
			return (ft_prnt_err("Error\nMutex init failure.\n"));
		}
		i++;
	}
	return (0);
}

// attempt lock function here
int	try_lock(t_philo_id *philo)
{
	
}

// attempt unlock function here

// destroy mutex locks here
int	destroy_mutex_locks(t_gen_stats *stats)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&stats->print_lock);
	while (i < stats->num_philos)
	{
		pthread_mutex_destroy(&stats->lock[i]);
		i++;
	}
	free(stats->lock);
	return (0);
}
