/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/27 21:47:51 by nhariman      #+#    #+#                 */
/*   Updated: 2021/08/19 18:40:26 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

#define FORK "has taken a fork"
#define EAT "eating"
#define THINK "thinking"
#define SLEEP "sleeping"
#define DIED "died"

enum    actions{
    eat,
    think,
    sleep,
    die
};

/*
** Philo struct
*/

typedef	struct	s_philo_id
{
	pthread_t	tid;
	long long	last_meal;
    pthread_mutex_t lock;
}				t_philo_id;

typedef struct  s_gen_stats
{
    long long	num_philos;
    long long	die;
    long long	eat;
    long long	sleep;
    long long	must_eat;
	t_philo_id	*philo_id;
    long long   start_time;
    bool        death;
}               t_gen_stats;

/*
** str functions
*/

int			is_digit(int c);
int         is_space(int c);
int         is_negative(int i);
void		ft_putstr_fd(char *str, int fd);
int			ft_strlen(char *str);
long long   ft_atoll(const char *nptr);

/*
** threading functions
*/



#endif