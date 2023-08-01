/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:32:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/08/01 14:30:34 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_full_behave(t_table *table, int count)
{
	pthread_mutex_lock(&table->lock);
	if (table->n_full == table->n_phil)
	{
		table->dead = 1;
		table->philo[count].died = 1;
		ft_philo_dead(table, count);
	}
	pthread_mutex_unlock(&table->lock);
}

void	*ft_monitor(void *vargp)
{
	t_table	*table;
	int		count;

	count = 0;
	table = (t_table *)vargp;
	ft_sleep(500);
	pthread_mutex_lock(&table->lock);
	table->start = 1;
	table->time_start = ft_gettime();
	pthread_mutex_unlock(&table->lock);
	ft_sleep(55);
	while (!table->dead)
	{
		ft_check_death(table, count);
		if (count == table->n_phil - 1)
			count = 0;
		else
			count++;
		usleep(500);
	}
	return (NULL);
}

void	*ft_onephilo(t_philo	*philo)
{
	int	died;

	died = 0;
	philo->state = THINK;
	ft_print_state(philo);
	pthread_mutex_lock(&philo->l_fork);
	philo->state = FORK;
	ft_print_state(philo);
	while (!died)
	{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->table->lock);
		died = philo->table->dead;
		pthread_mutex_unlock(&philo->table->lock);
		pthread_mutex_unlock(&philo->lock);
		usleep(100);
	}
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
