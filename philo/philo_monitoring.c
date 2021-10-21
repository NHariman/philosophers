/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_monitoring.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:59:58 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/21 15:29:30 by nhariman      ########   odam.nl         */
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

int	check_death(t_philo_id *philo)
{
	long long	time;
	int			ret;

	time = elapsed_time(philo->stats->start_time);
	ret = 0;
	if (time - philo->last_meal > philo->stats->die)
	{
		if (check_death_occurence(philo))
		{
			philo->death = true;
			return (1);
		}
		ft_mutex_print(philo, 0, "has \033[0;31mdied\033[0m");
		philo->death = true;
		pthread_mutex_lock(&philo->stats->death_lock);
		philo->stats->death_occured = true;
		pthread_mutex_unlock(&philo->stats->death_lock);
		ret = 1;
	}
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
