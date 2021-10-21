/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_lifecycle.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:59:29 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/21 18:38:13 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if a philosopher has died, set all philosopher statuses to dead
//so they can exit

static void	philo_living(t_philo_id *philo, int status)
{
	if (check_death_occurence(philo))
	{
		philo->death = true;
		return ;
	}
	if (status == eat)
	{
		ft_mutex_print(philo, 0, "is \033[0;33meating\033[0m");
		philo->meal_count += 1;
		philo->last_meal = elapsed_time(philo->stats->start_time);
		usleep(philo->stats->eat * 1000);
		drop_forks(philo);
	}
	else if (status == sleepy)
	{
		ft_mutex_print(philo, 0, "is \033[0;36msleeping\033[0m");
		usleep(philo->stats->sleep * 1000);
	}
	else if (status == think)
		ft_mutex_print(philo, 0, "is \033[0;32mthinking\033[0m");
}

static void	philo_action(t_philo_id *philo, int status)
{
	if (check_death_occurence(philo))
	{
		philo->death = true;
		return ;
	}
	if (check_death(philo))
		return ;
	else
		philo_living(philo, status);
}

static void	lifecycle(t_philo_id *philo)
{
	while (philo->death == false)
	{
		if (check_death_occurence(philo))
			return ;
		if (check_death(philo))
			return ;
		if (grab_forks(philo))
		{
			philo_action(philo, eat);
			philo_action(philo, sleepy);
			philo_action(philo, think);
		}
		if (philo->stats->must_eat != -2
			&& philo->meal_count
			== philo->stats->must_eat)
		{
			pthread_mutex_lock(&philo->stats->death_lock);
			philo->stats->death_occured = true;
			philo->death = true;
			pthread_mutex_unlock(&philo->stats->death_lock);
		}
		if (philo->stats->num_philos % 2 != 0
			&& philo->id == philo->stats->num_philos - 1)
			usleep(6000);
	}
}

// philosophers life here
void	*live_your_life(void *arg)
{
	t_philo_id	*philo;

	philo = (t_philo_id *)arg;
	if (philo->stats->num_philos == 1)
	{
		ft_mutex_print(philo, 0, "has \033[0;31mdied\033[0m");
		pthread_mutex_lock(&philo->stats->death_lock);
		philo->stats->death_occured = true;
		philo->death = true;
		pthread_mutex_unlock(&philo->stats->death_lock);
	}
	lifecycle(philo);
	return (NULL);
}
