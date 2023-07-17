/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:03:29 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/17 17:29:32 by fkrug            ###   ########.fr       */
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

	pthread_mutex_lock(&philo->table->lock);
	if (philo->table->dead == 0)
	{
		time = ft_gettime() - philo->table->time_start;
		if (philo->state == EAT)
			printf("%.0f ms %d %s", time, philo->id, EAT_MSG);
		else if (philo->state == THINK)
			printf("%.0f ms %d %s", time, philo->id, THINK_MSG);
		else if (philo->state == SLEEP)
			printf("%.0f ms %d %s", time, philo->id, SLEEP_MSG);
		else if (philo->state == FORK)
			printf("%.0f ms %d %s", time, philo->id, FORK_MSG);
	}
	pthread_mutex_unlock(&philo->table->lock);
}

void	ft_exit(t_table *table)
{
	
}