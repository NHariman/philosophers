/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 21:44:12 by niks          #+#    #+#                 */
/*   Updated: 2021/08/14 05:04:59 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*live_your_life(void *arg)
{
	t_gen_stats	*stats;

	stats = (t_gen_stats *)arg;
	while (1)
	{
		//life stuff
	}
}

int	create_philos(t_gen_stats *stats)
{
	int			i;
	int			*ret;

	i = 0;
	stats->philo_id = (t_philo_id *)malloc(stats->philos * sizeof(t_philo_id));
	while (i < stats->philos)
	{
		pthread_create(
			stats->philo_id[i].tid, NULL, &live_your_life, (void *)&stats);
		i++;
	}
	i = 0;
	while (i < stats->philos)
	{
		pthread_join(stats->philo_id[i].tid, &ret);
		i++;
	}
	return (*ret);
}
