/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_something.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: niks <niks@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/09 22:01:48 by niks          #+#    #+#                 */
/*   Updated: 2021/10/21 15:58:12 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_neg_or_zero(int i)
{
	if (i <= 0)
		return (1);
	return (0);
}
