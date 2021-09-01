/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 21:44:12 by niks          #+#    #+#                 */
/*   Updated: 2021/08/30 18:42:00 by nhariman      ########   odam.nl         */
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
	while (!philos->death || philo->stats->die < get_time() - philo->last_meal)
	{
		if (grab_fork(philo))
		{
			philo_action(philo, eat);
			philo_action(philo, sleepy);
		}
		else
			philo_action(philo, think);
	}
	philo_action(philo, die);
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
		if (pthread_mutex_init(&philo_id[i]->stats->lock[i], NULL))
			return (ft_prnt_err("Error\nMutex init failure.\n"));
		philo_id[i]->stats = &stats;
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
				philo_id[i].tid, NULL, &live_your_life, (void *)&philo_id[i]))
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
		if (pthread_join(philo_id[i].tid, &ret))
			return (ft_prnt_err("Error\nUnable to join threads\n"));
		i++;
	}
	return (0);
}

int	setup_philos(t_gen_stats *stats)
{
	int			*ret;
	t_philo_id	*philo_id;

	i = 0;
	philo_id = (t_philo_id *)
		malloc(stats->num_philos * sizeof(t_philo_id));
	philo_id->lock = (pthread_mutex_t *)malloc(
		stats->num_philos * sizeof(pthread_mutex_t))
	if (spawn_philo(&philo_id, *stats))
		return (1);
	if (create_philos(philo_id, stats->num_philos))
		return (1);
	if (join_philos(philo_id, stats->num_philos))
		return (1);
	return (0);
}
