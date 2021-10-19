/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos_do.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 17:05:31 by niks          #+#    #+#                 */
/*   Updated: 2021/09/30 18:41:52 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_lock(pthread_mutex_t *lock, int *stick)
{
	pthread_mutex_lock(lock);
	*stick = 1;
}

static void	philo_living(t_philo_id *philo, int status)
{
	if (philo->stats->death_occured)
		return ;
	if (status == eat)
	{
		ft_mutex_print(philo, 0, "is eating");
		usleep(philo->stats->eat * 1000);
		philo->last_meal = elapsed_time(philo->stats->start_time);
		put_down_fork(philo);
	}
	else if (status == sleepy)
	{
		ft_mutex_print(philo, 0, "is sleeping");
		usleep(philo->stats->sleep * 1000);
	}
	else if (status == think)
		ft_mutex_print(philo, 0, "is thinking");
}

int	ft_destroy_mutex(pthread_mutex_t *lock, long long num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_destroy(&lock[(num_philos - 1) - i]))
			return (ft_prnt_err("Error\nUnable to destroy mutex\n"));
		i++;
	}
	return (0);
}

void	philo_action(t_philo_id *philo, int status)
{
	long long	time;

	if (philo->stats->death_occured)
		return ;
	time = elapsed_time(philo->stats->start_time);
	if (time - philo->last_meal > philo->stats->die)
	{
		if (philo->stats->death_occured)
			return ;
		ft_mutex_print(philo, 0, "has died");
		philo->death = true;
		philo->stats->death_occured = true;
		return ;
	}
	else
		philo_living(philo, status);
}
