/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_monitoring.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:59:58 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/20 21:58:24 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_occurence(t_philo_id *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->stats->death_lock);
	if (philo->stats->death_occured == true)
		ret = 1;
	pthread_mutex_unlock(&philo->stats->death_lock);
	return (ret);
}

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
