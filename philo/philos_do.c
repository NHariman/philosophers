/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos_do.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/12 17:05:31 by niks          #+#    #+#                 */
/*   Updated: 2021/08/19 18:38:14 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_fork(t_gen_stats *stats)
{
	//grab right mutex_lock, so i + 1
	//if that does not work, grab left mutex lock, so i - 1
}

void	philo_action(t_gen_stats *stats, int status)
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