/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_death.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 21:54:27 by nhariman      #+#    #+#                 */
/*   Updated: 2021/11/03 22:30:58 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ft_mutex_print(philo, 0, "has \033[1;35meaten enough\033[0m");
// for being full

int	check_done_eating(t_philo_id *philo)
{
	int	ret;

	ret = 0;
	if (philo->stats->must_eat == -2)
		return (ret);
	pthread_mutex_lock(&philo->eat_lock);
	if (philo->stats->must_eat != -2
		&& philo->meal_count == philo->stats->must_eat)
	{
		ret = 1;
		ft_mutex_print(philo, 0, "has \033[0;32mfinished eating\033[0m");
	}
	pthread_mutex_unlock(&philo->eat_lock);
	return (ret);
}

int	check_pulse(t_philo_id *philo)
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
	pthread_mutex_lock(&philo->eat_lock);
	if (time - philo->last_meal > philo->stats->die)
	{
		pthread_mutex_unlock(&philo->eat_lock);
		ft_mutex_print(philo, 0, "has \033[0;31mdied\033[0m");
		pthread_mutex_lock(&philo->stats->death_lock);
		philo->stats->death_occured = true;
		pthread_mutex_unlock(&philo->stats->death_lock);
		ret = 1;
		philo->death = true;
	}
	else
		pthread_mutex_unlock(&philo->eat_lock);
	return (ret);
}

void	*life_support(void *args)
{
	t_philo_id	*philo;
	int			ret;

	ret = 0;
	philo = (t_philo_id *)args;
	while (1)
	{
		if (check_death(philo))
			ret = 1;
		if (check_done_eating(philo))
			ret = 1;
		if (ret)
			break ;
		mr_sandman(500);
	}
	return (NULL);
}

int	call_grimreaper(pthread_t *grimreaper, t_philo_id *philo)
{
	int			error;

	error = pthread_create(*&grimreaper, NULL, &life_support, (void *)philo);
	if (error)
	{
		pthread_mutex_lock(&philo->stats->death_lock);
		philo->stats->death_occured = true;
		pthread_mutex_unlock(&philo->stats->death_lock);
		return (1);
	}
	return (0);
}
