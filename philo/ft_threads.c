/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:32:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/15 13:42:49 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *myMonFunc(void *vargp)
{
	t_philo *philo = (t_philo *)vargp;

	philo->start_t = ft_gettime();
	while (philo->time_to_die > 0)
	{
		philo->time_to_die = philo->table->time_d + (long long)(philo->start_t - ft_gettime());
	}
	pthread_mutex_lock(&philo->table->lock);
	if (philo->table->dead == 0)
	{
		philo->table->dead = 1;
		printf("Philosopher %d %s", philo->id, DEAD_MSG);
	}
	pthread_mutex_unlock(&philo->table->lock);
	return (NULL);
}

void *myPhiloFunc(void *vargp)
{
	t_philo *philo = (t_philo *)vargp;
	if (pthread_create(&philo->mon_id, NULL, &myMonFunc, philo) != 0)
		return (NULL);
	while (!philo->table->dead)
	{
		printf("Philosopher %d %s", philo->id, THINK_MSG);
		pthread_mutex_lock(&philo->l_fork);
		//printf("Philosopher %d, locking left fork\n", philo->id);
		pthread_mutex_lock(philo->r_fork);
		printf("Philosopher %d %s", philo->id, FORK_MSG);
		printf("Philosopher %d %s", philo->id, EAT_MSG);
		ft_sleep(philo->table->time_e);
		//usleep(philo->table->time_e * 1000);
		philo->state = EAT;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
		philo->start_t = ft_gettime();
		printf("Philosopher %d %s", philo->id, SLEEP_MSG);
		ft_sleep(philo->table->time_s);
		//usleep(philo->table->time_s * 1000);
	}
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
	table->philo[count].time_to_die = table->time_d;
	table->philo[count].table = table;
	pthread_mutex_init(&table->philo[count].l_fork, NULL);
	if (count < table->n_phil - 1)
		table->philo[count].r_fork = &table->philo[count + 1].l_fork;
	else
		table->philo[count].r_fork = &table->philo[count + 1].l_fork;
	return (1);
}

int	ft_init_threads(t_table *table)
{
	int	count;

	pthread_mutex_init(&table->lock, NULL);
	count = -1;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->n_phil);
	table->dead = 0;
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
