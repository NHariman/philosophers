/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos_do.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 17:05:31 by niks          #+#    #+#                 */
/*   Updated: 2021/09/20 15:48:23 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_living(t_philo_id *philo, int status)
{
	if (status == eat)
	{
		printf("is eating\n");
		usleep(philo->stats->eat);
		philo->last_meal = elapsed_time(philo->stats->start_time);
		put_down_fork(philo);
	}
	else if (status == sleepy)
	{
		printf("is sleeping\n");
		usleep(philo->stats->sleep);
	}
	else if (status == sleep)
		printf("is thinking\n");
}

void	philo_action(t_philo_id *philo, int status)
{
	long long	time;

	if (philo->stats->death_occured)
		return ;
	time = elapsed_time(philo->stats->start_time);
	printf("[%lu] Philosopher no. %i ", time, philo->id);
	if (time - philo->last_meal > philo->stats->die)
	{
		philo->death = TRUE;
		philo->stats->death_occured = TRUE;
		printf("has died\n");
		return ;
	}
	else
		philo_living(philo, status);
}

/*
** the struct for reference:
**
** typedef	struct	s_philo_id
** {
**		pthread_t	tid;
**		long long   id;
** 	long long	last_meal;
**     pthread_mutex_t lock;
**     t_gen_stats *stats;
**     bool        death;
** }				t_philo_id;
** 
** typedef struct  s_gen_stats
** {
**     long long	num_philos;
**     long long	die;
**     long long	eat;
**     long long	sleep;
**     long long	must_eat;
**     long long   start_time;
**     bool        death_occured;
** }               t_gen_stats;
** 
*/
