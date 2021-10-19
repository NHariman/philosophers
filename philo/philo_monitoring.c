/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_monitoring.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:59:58 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/19 20:55:47 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_monitoring(t_gen_stats *stats, pthread_t *monitor)
{
	stats->death_occured = true;
	pthread_join(*monitor, NULL);
	return (1);
}

// create monitoring thread life cycle
void	*monitoring_system(void *args)
{
	t_gen_stats	*stats;

	stats = (t_gen_stats *)args;
	while (1)
	{
		pthread_mutex_lock(&stats->death_lock);
		if (stats->death_occured == true)
		{
			pthread_mutex_unlock(&stats->death_lock);
			break ;
		}
		pthread_mutex_unlock(&stats->death_lock);
		usleep(1000);
	}
	return (0);
}
