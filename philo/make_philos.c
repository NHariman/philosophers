/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 21:44:12 by niks          #+#    #+#                 */
/*   Updated: 2021/08/23 21:18:19 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//first play god and put everyting in 1 thread
// then branch out into separate threads which are all monitored by the first thread?

void	*live_your_life(void *arg)
{
	t_philo_id	*philos;

	philos = (t_philo_id *)arg;
	//pthread_mutex_lock()
	while (philos->death)
	{
		if (grab_fork(philos))
		{
			philo_action(philos, eat);
			philo_action(philos, sleepy);
		}
		else
			philo_action(philos, think);
	}
	philo_action(philos, die);
	return NULL;
}

int	spawn_philo(t_philo_id **philo_id, t_gen_stats stats)
{
	int	i;

	i = 0;
	while (i < stats.num_philos)
	{
		philo_id[i]->id = i;
		philo_id[i]->last_meal = 0;
		pthread_mutex_init(&philo_id[i]->lock , NULL);
		philo_id[i]->stats = &stats;
		philo_id[i]->death = false;
		i++;
	}
	return (1);
}

int	create_philos(t_gen_stats *stats)
{
	int			i;
	int			*ret;
	t_philo_id	*philo_id;

	i = 0;
	philo_id = (t_philo_id *)malloc(stats->num_philos * sizeof(t_philo_id));
	spawn_philo(&philo_id, *stats);
	while (i < stats->num_philos)
	{
		// if cannot create thread, die.
		pthread_create(
			philo_id[i].tid, NULL, &live_your_life, (void *)&philo_id);
		i++;
	}
	i = 0;
	while (i < stats->num_philos)
	{
		pthread_join(philo_id[i].tid, &ret);
		i++;
	}
	return (*ret);
}
