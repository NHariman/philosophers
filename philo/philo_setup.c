/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_setup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:24:04 by nhariman      #+#    #+#                 */
/*   Updated: 2021/09/30 21:46:14 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// create threads function here
static int	create_threads(t_gen_stats *stats)

// join threads function here

int	setup_philos(t_gen_stats *stats)
{
	if (initialise_mutex_locks(stats) != 0)
		return (1);
	// create threads
	// join threads
	if (destroy_mutex_locks(stats) != 0)
		return (1);
}
