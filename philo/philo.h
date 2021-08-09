/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niks <niks@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 21:47:51 by nhariman          #+#    #+#             */
/*   Updated: 2021/08/10 00:46:38 by niks             ###   ########.fr       */
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

/*
** Philo struct
*/
typedef struct  s_philo_stats
{
    long long philos;
    long long die;
    long long eat;
    long long sleep;
    long long must_eat;
}               t_philo_stats;

/*
** str functions
*/

void		ft_putstr_fd(char *str, int fd);
int			ft_strlen(char *str);
int			is_digit(int c);
int			is_space(int c);
int			is_negative(int i);
long long	ft_atoll(const char *nptr);

#endif