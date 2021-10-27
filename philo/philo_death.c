/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_death.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 21:54:27 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/27 17:32:38 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	call_grimreaper(t_philo_id *philo)
{
	pthread_t	grimreaper;
	int			error;

	error = pthread_create(&grimreaper, NULL, &life_support, (void *)philo);
	if (error)
	{
		pthread_mutex_lock(&philo->stats->death_lock);
		philo->stats->death_occured = true;
		pthread_mutex_unlock(&philo->stats->death_lock);
		return (1);
	}
	pthread_detach(grimreaper);
	return (0);
}

// ft_mutex_print(philo, 0, "has \033[1;35meaten enough\033[0m");
// for being full
void	*life_support(void *args)
{
	t_philo_id	*philo;

	philo = (t_philo_id *)args;
	while (1)
	{
		if (check_death(philo))
			break ;
		pthread_mutex_lock(&stats->death_lock);
		if (stats->death_occured == true)
		{
			pthread_mutex_unlock(&stats->death_lock);
			break ;
		}
		pthread_mutex_unlock(&stats->death_lock);
		if (stats->must_eat != -2)
		{
			pthread_mutex_lock(&stats->eat_lock);
			if (stats->done_eating == stats->num_philos)
			{
				pthread_mutex_unlock(&stats->eat_lock);
				break ;
			}
			pthread_mutex_unlock(&stats->eat_lock);
		}
		usleep(10);
	}
	pthread_mutex_lock(&philo->stats->death_lock);
	philo->stats->death_occured = true;
	pthread_mutex_unlock(&philo->stats->death_lock);
	return (NULL);
}

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

	ret = 0;
	time = elapsed_time(philo->stats->start_time);
	pthread_mutex_lock(&philo->stats->eat_lock);
	if (time - philo->last_meal > philo->stats->die)
	{
		pthread_mutex_unlock(&philo->stats->eat_lock);
		ft_mutex_print(philo, 0, "has \033[0;31mdied\033[0m");
		philo->death = true;
		ret = 1;
	}
	else
		pthread_mutex_unlock(&philo->stats->eat_lock);
	return (ret);
}
