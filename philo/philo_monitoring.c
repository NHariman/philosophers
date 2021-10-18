/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_monitoring.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:59:58 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/18 21:53:42 by nhariman      ########   odam.nl         */
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
	while (stats->death_occured == false)
	{
		usleep(1000);
		// if (stats->must_eat != -2
		// 	&& stats->meal_count
		// 	== stats->must_eat * (stats->num_philos))
		// 	stats->death_occured = true;
	}
	return (0);
}
