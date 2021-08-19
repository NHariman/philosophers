/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 21:44:12 by niks          #+#    #+#                 */
/*   Updated: 2021/08/19 18:40:46 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*live_your_life(void *arg)
{
	t_gen_stats	*stats;

	stats = (t_gen_stats *)arg;
	//initiate mutex
	while (!stats->death)
	{
		if (grab_fork(stats))
		{
			philo_action(stats, eat);
			philo_action(stats, sleep);
		}
		else
			philo_action(stats, think);
	}
	philo_action(stats, die);
	return ;
}

int	create_philos(t_gen_stats *stats)
{
	int			i;
	int			*ret;

	i = 0;
	stats->philo_id = (t_philo_id *)malloc(stats->num_philos * sizeof(t_philo_id));
	while (i < stats->num_philos)
	{
		// if cannot create thread, die.
		pthread_create(
			stats->philo_id[i].tid, NULL, &live_your_life, (void *)&stats);
		i++;
	}
	i = 0;
	while (i < stats->num_philos)
	{
		pthread_join(stats->philo_id[i].tid, &ret);
		i++;
	}
	return (*ret);
}
