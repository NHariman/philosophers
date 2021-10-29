/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_death.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 21:54:27 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/29 20:34:47 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ft_mutex_print(philo, 0, "has \033[1;35meaten enough\033[0m");
// for being full
void	*life_support(void *args)
{
	t_philo_id	*philo;
	int			ret;

	philo = (t_philo_id *)args;
	while (1)
	{
		if (check_death(philo))
			ret = 1;
		if (check_done_eating(philo))
			ret = 1;
		if (ret)
			break ;
		usleep(100);
	}
	return (NULL);
}

int	check_done_eating(t_philo_id *philo)
{
	int	ret;

	ret = 0;
	if (philo->stats->must_eat == -2)
		return (ret);
	pthread_mutex_lock(&philo->eat_lock);
	if (philo->stats->must_eat != -2
		&& philo->meal_count >= philo->stats->must_eat)
		ret = 1;
	pthread_mutex_unlock(&philo->eat_lock);
	return (ret);
}

int	check_death(t_philo_id *philo)
{
	long long	time;
	int			ret;

	ret = 0;
	pthread_mutex_lock(&philo->stats->death_lock);
	pthread_mutex_lock(&philo->eat_lock);
	time = elapsed_time(philo->stats->start_time);
	if (philo->stats->death_occured == true
		|| time - philo->last_meal > philo->stats->die)
	{
		ret = 1;
		philo->stats->death_occured = true;
	}
	pthread_mutex_unlock(&philo->eat_lock);
	pthread_mutex_unlock(&philo->stats->death_lock);
	return (ret);
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
