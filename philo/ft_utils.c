/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:56:09 by fkrug             #+#    #+#             */
/*   Updated: 2023/08/01 14:12:57 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_mgmt(int errno)
{
	char	*str;

	str = NULL;
	if (errno == MISSING_ARG)
		str = "Error: Missing arguments\n";
	else if (errno == NO_NUMBER)
		str = "Error: Not a number\n";
	else if (errno == LIMIT)
		str = "Error: Numbers out of range\n";
	else if (errno == NEG_NUMBER)
		str = "Error: Negative numbers not allowed\n";
	else if (errno == PHIL_RANGE)
		str = "Error: Philosophers out of range\n";
	else if (errno == MIN_TIME)
		str = "Error: Please choose time at least equal to 60ms\n";
	printf("%s", str);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long	ft_atoi(const char *nptr)
{
	long long	n;
	int			sign;

	n = 0;
	sign = 1;
	while (*nptr && ((8 < *nptr && 14 > *nptr) || *nptr == 32))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		n *= 10;
		n = n + *nptr - 48;
		nptr++;
	}
	n *= sign;
	return (n);
}

int	ft_input_test(int argc, char **argv)
{
	int		c_0;
	int		c_1;
	char	*str;

	c_0 = 1;
	c_1 = 0;
	while (c_0 < argc)
	{
		c_1 = 0;
		str = argv[c_0];
		while (str[c_1])
		{
			if (c_1 != 0 && (str[c_1] == '-' || str[c_1] == '+'))
				return (ft_error_mgmt(NO_NUMBER));
			else if (!ft_isdigit(str[c_1]) && c_1 != 0)
				return (ft_error_mgmt(NO_NUMBER));
			c_1++;
		}
		c_0++;
	}
	return (0);
}

void	ft_free(t_table *table)
{
	int	count;

	count = -1;
	while (++count < table->n_phil)
		pthread_mutex_destroy(&table->philo[count].l_fork);
	pthread_mutex_destroy(&table->full);
	pthread_mutex_destroy(&table->lock);
	pthread_mutex_destroy(&table->write);
	free(table->philo);
}
