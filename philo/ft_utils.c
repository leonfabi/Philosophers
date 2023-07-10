/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:56:09 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/10 09:18:03 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_mgmt(int errno)
{
	if (errno == MISSING_ARG)
		printf(MISSING_ARG_MSG);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

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
	int		count;
	char	*str;

	count = 1;
	
}
