/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos_do.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 17:05:31 by niks          #+#    #+#                 */
/*   Updated: 2021/09/01 18:01:19 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec) * 1000 + (time.tv_usec) / 1000);
}

void	grab_fork(t_philo_id *philo)
{
	if (philo->stats->num_philos > 1)
		if (philo->id == 0)
		{
			if (//try to grab right fork)
				philo->stats->lock[philo->id + 1];
			else if (//try to grab left fork)
				philo->stats->lock[philo->stats->num_philos - 1];
			else
				return (0);
		
	//grab right mutex_lock, so i + 1
	//if that does not work, grab left mutex lock, so i - 1
}

void	philo_action(t_philo_id *philo, int status)
{
	//get time and subtract start time for elapsed time
	//get last meal time and subtract elapsed time from last meal
	// if this value is larger than death time
	// kill the philosopher and end the process.
	// don't forget to change the bool of death to TRUE
	// also unlock mutex
	//check status, what's supposed to happen?
	//print what happened
	//sleep for the appropriate time
	// if eating, unlock.
}