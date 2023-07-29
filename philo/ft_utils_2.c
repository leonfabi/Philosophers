/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:03:29 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/29 14:13:09 by fkrug            ###   ########.fr       */
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
	int		dead;

	str = NULL;
	pthread_mutex_lock(&philo->table->lock);
	dead = philo->table->dead;
	pthread_mutex_unlock(&philo->table->lock);
	pthread_mutex_lock(&philo->table->write);
	if (dead == 0)
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
	time = ft_gettime() - philo->table->time_start;
	if (str != NULL)
		printf("%.0f %d %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->write);
}

void	ft_philo_dead(t_table *table, int count)
{
	int	i;

	i = -1;
	while (++i < table->n_phil)
	{
		if (i != count)
			table->philo[i].died = 1;
	}
}
