/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:56:09 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/10 13:55:21 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_mgmt(int errno)
{
	if (errno == MISSING_ARG)
		printf(MISSING_ARG_MSG);
	if (errno == NO_NUMBER)
		printf(NO_NUMBER_MSG);
	if (errno == LIMIT)
		printf(LIMIT_MSG);
	if (errno == NEG_NUMBER)
		printf(NEG_NUMBER_MSG);
	if (errno == PHIL_RANGE)
		printf(PHIL_RANGE_MSG);
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

int	ft_input_check(int argc, char **argv)
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
	free(table->philo);
}
