/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/27 21:47:51 by nhariman      #+#    #+#                 */
/*   Updated: 2021/07/27 22:05:16 by nhariman      ########   odam.nl         */
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
** str functions
*/

void	ft_putstr_fd(char *str, int fd);
int		ft_strlen(char *str);

#endif