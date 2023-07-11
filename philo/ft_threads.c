/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:32:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/11 13:48:31 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *myMonFunc(void *vargp)
{
	t_philo *philo = (t_philo *)vargp;
	double	tmp = 0;
	gettimeofday(&philo->start_time, NULL);
	gettimeofday(&philo->time, NULL);
	while (tmp >= 0)
	{
	// printf("Start time: %ld Remaining time: %lld Philosopher %d %s",philo->start_time.tv_usec, tmp, philo->id, THINK_MSG);
		gettimeofday(&philo->time, NULL);
		tmp = (double)((philo->start_time.tv_sec - philo->time.tv_sec) * 1000000LL + philo->start_time.tv_usec - philo->time.tv_usec) / 1000000;
	}
}

void *myPhiloFunc(void *vargp)
{
	t_philo *philo = (t_philo *)vargp;
	if (pthread_create(&philo->mon_id, NULL, &myMonFunc, philo) != 0)
		return (NULL);
	if (pthread_join(philo->mon_id, NULL) != 0)
		return (NULL);
	// gettimeofday(&philo->start_time, NULL);
	// printf("Start time: %ld Philosopher %d %sTime to die: %d\n",philo->start_time.tv_usec, philo->id, THINK_MSG, philo->table->time_d);
	return (NULL);
}

int	ft_init_philo(t_table *table, int count)
{
	table->philo[count].id = count + 1;
	table->philo[count].state = THINK;
	table->philo[count].table = table;
	pthread_mutex_init(&table->philo[count].l_fork, NULL);
}

int	ft_init_threads(t_table *table)
{
	int	count;

	count = -1;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->n_phil);
	if (!table->philo)
	{
		free(table->philo);
		table->philo = NULL;
		return (1);
	}
	while (++count < table->n_phil)
	{
		ft_init_philo(table, count);
		if (pthread_create(&(table->philo[count].thread_id), NULL, &myPhiloFunc, &(table->philo[count])) != 0)
			return (EXIT_FAILURE);
	}
	count = -1;
	while (++count < table->n_phil)
	{
		if (pthread_join(table->philo[count].thread_id, NULL) != 0)
			return (EXIT_FAILURE);
		count++;
	}
	return (0);
}
