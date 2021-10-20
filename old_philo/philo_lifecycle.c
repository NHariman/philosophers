/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_lifecycle.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 20:21:25 by nhariman      #+#    #+#                 */
/*   Updated: 2021/09/30 18:37:32 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*live_your_life(void *arg)
{
	t_philo_id	*philo;

	philo = (t_philo_id *)arg;
	while (philo->stats->death_occured == false)
	{
		if (grab_fork(philo))
		{
			philo_action(philo, eat);
			philo_action(philo, sleepy);
			philo_action(philo, think);
		}
	}
	return (NULL);
}

int	create_philos(t_philo_id *philo_id, long long num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_create(
				&philo_id[i].tid, NULL, &live_your_life, (void *)&philo_id[i]))
			return (ft_prnt_err("Error\nFailure to create thread.\n"));
		i++;
	}
	return (0);
}
