/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_lifecycle.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:59:29 by nhariman      #+#    #+#                 */
/*   Updated: 2021/11/24 16:40:05 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if a philosopher has died, set all philosopher statuses to dead
//so they can exit

//ft_mutex_print(philo, 0, "is \033[0;32mthinking\033[0m");
static void	philo_action(t_philo_id *philo, int status)
{
	if (status == eat)
	{
		grab_forks(philo);
		ft_mutex_print(philo, 0, "is \033[0;33meating\033[0m");
		pthread_mutex_lock(&philo->eat_lock);
		philo->meal_count += 1;
		philo->last_meal = elapsed_time(philo->stats->start_time);
		pthread_mutex_unlock(&philo->eat_lock);
		mr_sandman(philo->stats->eat);
		drop_forks(philo);
	}
	else if (status == sleepy)
	{
		ft_mutex_print(philo, 0, "is \033[0;36msleeping\033[0m");
		mr_sandman(philo->stats->sleep);
	}
	else if (status == think)
		ft_mutex_print(philo, 0, "is \033[0;32mthinking\033[0m");
}

static void	lifecycle(t_philo_id *philo)
{
	philo->last_meal = elapsed_time(philo->stats->start_time);
	while (1)
	{
		if (check_pulse(philo))
			return ;
		philo_action(philo, eat);
		if (check_done_eating(philo))
			return ;
		philo_action(philo, sleepy);
		philo_action(philo, think);
		if (philo->stats->num_philos % 2 != 0
			&& philo->id == philo->stats->num_philos - 1)
			mr_sandman(6);
	}
}

// philosophers life here
void	*live_your_life(void *arg)
{
	t_philo_id	*philo;
	pthread_t	grimreaper;

	philo = (t_philo_id *)arg;
	grimreaper = 0;
	call_grimreaper(&grimreaper, philo);
	if (philo->stats->num_philos == 1)
	{
		ft_mutex_print(philo, 0, "is \033[0;32mthinking\033[0m");
		mr_sandman(philo->stats->die);
		ft_mutex_print(philo, 0, "has \033[0;31mdied\033[0m");
		pthread_mutex_lock(&philo->stats->death_lock);
		philo->stats->death_occured = true;
		pthread_mutex_unlock(&philo->stats->death_lock);
		philo->death = true;
	}
	lifecycle(philo);
	pthread_join(grimreaper, NULL);
	pthread_mutex_destroy(&philo->eat_lock);
	return (NULL);
}
