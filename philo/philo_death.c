/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_death.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 21:54:27 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/26 22:22:04 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		call_grimreaper(t_philo_id *philo)
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
	return (0);
}

void	*life_support(void *args)
{
	t_philo_id	*philo;

	philo = (t_philo_id *)args;
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		usleep(10);
	}
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
		pthread_mutex_lock(&philo->die_lock);
		philo->death = true;
		pthread_mutex_unlock(&philo->die_lock);
		pthread_mutex_lock(&philo->stats->death_lock);
		philo->stats->death_occured = true;
		pthread_mutex_unlock(&philo->stats->death_lock);
		ret = 1;
	}
	return (ret);
}
