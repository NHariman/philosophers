/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_monitoring.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 19:59:58 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/04 19:41:40 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		end_monitoring(t_gen_stats *stats)
{
	stats->death_occured = true;
	return (1);
}

// create monitoring thread life cycle
void	*monitoring_system(void *args)
{
	t_gen_stats	*stats;

	stats = (t_gen_stats *)args;
	while (stats->death_occured == false)
	{
		usleep(100);
	}
	return (0);
}
