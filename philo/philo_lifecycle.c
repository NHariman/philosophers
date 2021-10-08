/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_lifecycle.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:59:29 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/08 17:33:12 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if a philosopher has died, set all philosopher statuses to dead
//so they can exit

static void	philo_living(t_philo_id *philo, int status)
{
	if (philo->stats->death_occured)
		return ;
	if (status == eat)
	{
		ft_mutex_print(philo, 0, "is eating");
		usleep(philo->stats->eat * 1000);
		philo->last_meal = elapsed_time(philo->stats->start_time);
		drop_forks(philo);
	}
	else if (status == sleepy)
	{
		ft_mutex_print(philo, 0, "is sleeping");
		usleep(philo->stats->sleep * 1000);
	}
	else if (status == think)
		ft_mutex_print(philo, 0, "is thinking");
}

static void	philo_action(t_philo_id *philo, int status)
{
	long long	time;

	if (philo->stats->death_occured)
	{
		philo->death = true;
		return ;
	}
	time = elapsed_time(philo->stats->start_time);
	if (time - philo->last_meal > philo->stats->die)
	{
		if (philo->stats->death_occured)
		{
			philo->death = true;
			return ;
		}
		ft_mutex_print(philo, 0, "has died");
		philo->death = true;
		philo->stats->death_occured = true;
		return ;
	}
	else
		philo_living(philo, status);
}

// philosophers life here
void	*live_your_life(void *arg)
{
	t_philo_id	*philo;

	philo = (t_philo_id *)arg;
	while (philo->stats->death_occured == false || philo->death == true)
	{
		if (grab_forks(philo))
		{
			philo_action(philo, think);
			philo_action(philo, eat);
			philo_action(philo, sleepy);
		}
	}
	return (NULL);
}
