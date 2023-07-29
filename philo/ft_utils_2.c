/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:03:29 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/29 13:16:44 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

__uint64_t	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((__uint64_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	ft_sleep(__uint64_t ms)
{
	__uint64_t	init;

	init = ft_gettime();
	while ((ft_gettime() - init) < ms)
		usleep(100);
	return ;
}

void	ft_print_state(t_philo *philo)
{
	double	time;
	char	*str;

	str = NULL;
	pthread_mutex_lock(&philo->table->lock);
	if (philo->table->dead == 0)
	{
		if (philo->state == EAT)
			str = "is eating\n";
		else if (philo->state == THINK)
			str = "is thinking\n";
		else if (philo->state == SLEEP)
			str = "is sleeping\n";
		else if (philo->state == FORK)
			str = "has taken a fork\n";
	}
	pthread_mutex_unlock(&philo->table->lock);
	if (str != NULL)
	{
	pthread_mutex_lock(&philo->table->write);
	time = ft_gettime() - philo->table->time_start;
	printf("%.0f %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->write);
	}
}
