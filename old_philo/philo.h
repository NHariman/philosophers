/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/30 15:15:43 by nhariman      #+#    #+#                 */
/*   Updated: 2021/09/21 18:17:26 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

enum	e_actions{
	eat,
	think,
	sleepy,
	die
};

/*
** Philo struct
*/

typedef struct s_gen_stats
{
	long long		num_philos;
	pthread_mutex_t	*lock;
	pthread_mutex_t	print_lock;
	long long		die;
	long long		eat;
	long long		sleep;
	long long		must_eat;
	long long		start_time;
	bool			death_occured;
}				t_gen_stats;

typedef struct s_philo_id
{
	pthread_t		tid;
	long long		id;
	long long		last_meal;
	t_gen_stats		*stats;
	bool			death;
}				t_philo_id;

/*
** str and number functions
*/

int			is_digit(int c);
int			is_space(int c);
int			is_negative(int i);
void		ft_putstr_fd(char *str, int fd);
int			ft_prnt_err(char *str);
int			ft_strlen(char *str);
long long	ft_atoll(const char *nptr);
int			ft_mutex_print(t_philo_id *philo, int ret, char *action);

/*
** get time
*/
long long	get_time(void);
long long	elapsed_time(long long start_time);

/*
** threading functions
*/
int			setup_philos(t_gen_stats *stats);
int			grab_fork(t_philo_id *philo);
int			put_down_fork(t_philo_id *philo);
int			ft_destroy_mutex(pthread_mutex_t *lock, long long num_philos);

/*
** Philosopher actions and living
*/
void		philo_action(t_philo_id *philo, int status);
void		philo_lock(pthread_mutex_t *lock, int *stick);

#endif