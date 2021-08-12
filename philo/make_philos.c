/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niks <niks@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 21:44:12 by niks              #+#    #+#             */
/*   Updated: 2021/08/12 22:39:30 by niks             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*live_your_life(void *arg)
{
	t_gen_stats	stats;

	stats = (t_gen_stats)*arg;
	while (1)
	{
		//life stuff
	}
}

int    create_philos(t_philo_stats stats)
{
	int			i;
	int			*ret;

	stat.philo_id = (t_philo_id *)malloc(stats.philos * sizeof(t_philo_id));
	while (i < stats.philos)
	{
		pthread_create(&stats.philo_id[i]->tid, NULL, live_your_life, (void *)&stats);
		i++;
	}
	pthread_join(tid, &ret);
	return (*ret);
}