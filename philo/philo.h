/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/30 15:15:43 by nhariman      #+#    #+#                 */
/*   Updated: 2021/10/18 21:18:52 by nhariman      ########   odam.nl         */
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
	long long		meal_count;
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
** Philo functions
*/
int			setup_philos(t_gen_stats *stats);
void		*monitoring_system(void *args);
int			end_monitoring(t_gen_stats *stats, pthread_t *monitor);
void		*live_your_life(void *arg);

// mutex
int			destroy_mutex_locks(t_gen_stats *stats);
int			initialise_mutex_locks(t_gen_stats *stats);
int			grab_forks(t_philo_id *philo);
int			drop_forks(t_philo_id *philo);

#endif