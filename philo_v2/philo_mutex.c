/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_mutex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:47:47 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/26 22:33:35 by nhariman      ########   odam.nl         */
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
	if (pthread_mutex_init(&stats->death_lock, NULL) != 0)
		return (ft_prnt_err("Error\nMutex init failure.\n"));
	if (pthread_mutex_init(&stats->eat_lock, NULL) != 0)
		return (ft_prnt_err("Error\nMutex init failure.\n"));
	stats->lock = (pthread_mutex_t *)malloc(
			stats->num_philos * sizeof(pthread_mutex_t));
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
int	grab_forks(t_philo_id *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->stats->lock[philo->id]);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->stats->lock[philo->stats->num_philos - 1]);
	else
		pthread_mutex_lock(&philo->stats->lock[philo->id - 1]);
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&philo->stats->lock[philo->id]);
	ft_mutex_print(philo, 0, "has \033[0;34mtaken a fork\033[0m");
	return (1);
}

// attempt unlock function here
int	drop_forks(t_philo_id *philo)
{
	pthread_mutex_unlock(&philo->stats->lock[philo->id]);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo->stats->lock[philo->stats->num_philos - 1]);
	else
		pthread_mutex_unlock(&philo->stats->lock[philo->id - 1]);
	return (1);
}

// destroy mutex locks here
int	destroy_mutex_locks(t_gen_stats *stats)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&stats->print_lock);
	pthread_mutex_destroy(&stats->death_lock);
	pthread_mutex_destroy(&stats->eat_lock);
	while (i < stats->num_philos)
	{
		pthread_mutex_destroy(&stats->lock[i]);
		i++;
	}
	free(stats->lock);
	return (0);
}
