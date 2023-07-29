/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:32:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/29 11:57:17 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*ft_monitor(void *vargp)
{
	t_table	*table;
	int		count;

	count = 0;
	table = (t_table *)vargp;
	ft_sleep(2000);
	pthread_mutex_lock(&table->lock);
	table->start = 1;
	table->time_start = ft_gettime();
	pthread_mutex_unlock(&table->lock);
	ft_sleep(30);
	while (!table->dead)
	{
		pthread_mutex_lock(&table->philo[count].lock);
		table->philo[count].time_to_die = table->time_d \
		+ (long long)(table->philo[count].start_t - ft_gettime());
		if (table->philo[count].time_to_die < 0)
		{
			// printf("table->philo[%d].time_to_die: %f, table->philo[%d].start_t - ft_gettime(): %lld\n", count, table->philo[count].time_to_die, count, (long long)(table->philo[count].start_t - ft_gettime()));
			pthread_mutex_lock(&table->lock);
			if (table->dead == 0)
			{
				table->dead = 1;
				table->philo[count].died = 1;
				ft_philo_dead(table, count);
				pthread_mutex_lock(&table->write);
				printf("%.0f %d %s", ft_gettime() \
				- table->time_start, table->philo[count].id, DEAD_MSG);
				pthread_mutex_unlock(&table->write);
			}
			pthread_mutex_unlock(&table->lock);
		}
		pthread_mutex_unlock(&table->philo[count].lock);
		if (count == table->n_phil - 1)
			count = 0;
		else
			count++;
	}
	return NULL;
}

void	*ft_onephilo(void *vargp)
{
	t_philo	*philo;

	philo = (t_philo *)vargp;
	philo->state = THINK;
	ft_print_state(philo);
	pthread_mutex_lock(&philo->l_fork);
	philo->state = FORK;
	ft_print_state(philo);
	while (!philo->table->dead)
		usleep(10);
	pthread_mutex_unlock(&philo->l_fork);
	return (NULL);
}

void	*myphilofunc(void *vargp)
{
	t_philo	*philo;
	int		start;

	start = 0;
	philo = (t_philo *)vargp;
	while (start != 1)
	{
		pthread_mutex_lock(&philo->table->lock);
		start = philo->table->start;
		pthread_mutex_unlock(&philo->table->lock);
		usleep(10);
	}
	pthread_mutex_lock(&philo->lock);
	philo->start_t = ft_gettime();
	pthread_mutex_unlock(&philo->lock);
	if (philo->table->n_phil == 1)
		return (ft_onephilo(philo));
	// while (!philo->table->dead)
	while (!philo->died)
		ft_action(philo);
	return (NULL);
}

int	ft_init_threads(t_table *table)
{
	int	count;

	count = -1;
	while (++count < table->n_phil)
	{
		if (pthread_create(&(table->philo[count].thread_id), \
		NULL, &myphilofunc, &(table->philo[count])) != 0)
			return (EXIT_FAILURE);
	}
	if (pthread_create(&table->monitor, NULL, &ft_monitor, table) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(table->monitor, NULL) != 0)
		return (EXIT_FAILURE);
	count = -1;
	while (++count < table->n_phil)
	{
		if (pthread_join(table->philo[count].thread_id, NULL) != 0)
			return (EXIT_FAILURE);
	}
	return (0);
}
