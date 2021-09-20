/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 21:44:12 by niks          #+#    #+#                 */
/*   Updated: 2021/09/20 18:50:28 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** first play god and put everyting in 1 thread
** then branch out into separate threads
** which are all monitored by the first thread?
*/

static void	*live_your_life(void *arg)
{
	t_philo_id	*philo;

	philo = (t_philo_id *)arg;
	while (!philo->stats->death_occured || !philo->death
		|| philo->stats->die < elapsed_time(
			philo->stats->start_time) - philo->last_meal)
	{
		if (grab_fork(philo))
		{
			philo_action(philo, eat);
			philo_action(philo, sleepy);
		}
		else
			philo_action(philo, think);
	}
	return (NULL);
}

static int	spawn_philo(t_philo_id **philo_id, t_gen_stats stats)
{
	int	i;

	i = 0;
	while (i < stats.num_philos)
	{
		philo_id[i]->id = i;
		philo_id[i]->last_meal = 0;
		philo_id[i]->stats = &stats;
		if (pthread_mutex_init(&philo_id[i]->stats->lock[i], NULL))
			return (ft_prnt_err("Error\nMutex init failure.\n"));
		philo_id[i]->death = false;
		i++;
	}
	return (0);
}

static int	create_philos(t_philo_id *philo_id, long long num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_create(
				&philo_id[i].tid, NULL, &live_your_life, (void *)&philo_id[i]))
			return (ft_prnt_err("Error\nFailure to create thread.\n"));
		i++;
	}
	return (0);
}

static int	join_philos(t_philo_id *philo_id, long long num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_join(philo_id[i].tid, NULL))
			return (ft_prnt_err("Error\nUnable to join threads\n"));
		i++;
	}
	return (0);
}

int	setup_philos(t_gen_stats *stats)
{
	t_philo_id	*philo_id;

	philo_id = (t_philo_id *)
		malloc(stats->num_philos * sizeof(t_philo_id));
	if (!philo_id)
		return (ft_prnt_err("Error\nMalloc failure.\n"));
	stats->lock = (pthread_mutex_t *)
		malloc(stats->num_philos * sizeof(pthread_mutex_t));
	if (!stats->lock)
		return (ft_prnt_err("Error\nMalloc failure.\n"));
	printf("Malloced succesfully\n");
	if (spawn_philo(&philo_id, *stats))
		return (1);
	printf("spawn_philo succesfully\n");
	if (create_philos(philo_id, stats->num_philos))
		return (1);
	printf("create_philo succesfully\n");
	if (join_philos(philo_id, stats->num_philos))
		return (1);
	printf("join_philo succesfully\n");
	return (0);
}
