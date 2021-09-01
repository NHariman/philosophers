/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/30 15:15:43 by nhariman      #+#    #+#                 */
/*   Updated: 2021/08/30 18:32:56 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FORK "has taken a fork"
# define EAT "eating"
# define THINK "thinking"
# define SLEEP "sleeping"
# define DIED "died"

# include <string.h>
# include <unistd.h>
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

typedef struct s_philo_id
{
	pthread_t		tid;
	long long		id;
	long long		last_meal;
	t_gen_stats		*stats;
	bool			death;
}				t_philo_id;

typedef struct s_gen_stats
{
	long long		num_philos;
	pthread_mutex_t	*lock;
	long long		die;
	long long		eat;
	long long		sleep;
	long long		must_eat;
	long long		start_time;
	bool			death_occured;
}				t_gen_stats;

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

/*
** get time
*/
long		get_time(void);

/*
** threading functions
*/
int			setup_philos(t_gen_stats *stats);
int			grab_fork(t_philo_id *philo);

#endif