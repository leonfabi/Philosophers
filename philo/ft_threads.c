/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:32:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/17 21:23:54 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*mymonfunc(void *vargp)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)vargp;
// 	philo->start_t = ft_gettime();
// 	while (philo->time_to_die > 0)
// 	{
// 		pthread_mutex_lock(&philo->lock);
// 		philo->time_to_die = philo->table->time_d \
// 		+ (long long)(philo->start_t - ft_gettime());
// 		pthread_mutex_unlock(&philo->lock);
// 		usleep(10);
// 	}
// 	pthread_mutex_lock(&philo->table->lock);
// 	if (philo->table->dead == 0)
// 	{
// 		philo->table->dead = 1;
// 		printf("%.0f ms %d %s", ft_gettime() \
// 		- philo->table->time_start, philo->id, DEAD_MSG);
// 	}
// 	pthread_mutex_unlock(&philo->table->lock);
// 	return (NULL);
// }

void	*mymonfunc(void *vargp)
{
	t_philo	*philo;

	philo = (t_philo *)vargp;
	philo->start_t = ft_gettime();
	while (philo->table->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		philo->time_to_die = philo->table->time_d \
		+ (long long)(philo->start_t - ft_gettime());
		if (philo->time_to_die < 0 && philo->state != EAT)
		{
			pthread_mutex_lock(&philo->table->lock);
			if (philo->table->dead == 0)
			{
				philo->table->dead = 1;
				printf("%.0f ms %d %s", ft_gettime() \
				- philo->table->time_start, philo->id, DEAD_MSG);
			}
			pthread_mutex_unlock(&philo->table->lock);
		}
		pthread_mutex_unlock(&philo->lock);
		usleep(10);
	}
	return (NULL);
}

void	*ft_onephilo(void *vargp)
{
	t_philo	*philo;

	philo = (t_philo *)vargp;
	philo->state = THINK;
	ft_print_state(philo);
	while (!philo->table->dead)
		usleep(10);
	return (NULL);
}

void	*myphilofunc(void *vargp)
{
	t_philo	*philo;

	philo = (t_philo *)vargp;
	if (pthread_create(&philo->mon_id, NULL, &mymonfunc, philo) != 0)
		return (NULL);
	if (philo->table->n_phil == 1)
	{
		if (pthread_join(philo->mon_id, NULL) != 0)
			return (NULL);
		return (ft_onephilo(philo));
	}
	while (!philo->table->dead)
		ft_action(philo);
	if (pthread_join(philo->mon_id, NULL) != 0)
		return (NULL);
	return (NULL);
}

int	ft_init_philo(t_table *table, int count)
{
	table->philo[count].id = count + 1;
	table->philo[count].state = THINK;
	table->philo[count].time_to_die = table->time_d;
	table->philo[count].table = table;
	pthread_mutex_init(&table->philo[count].l_fork, NULL);
	pthread_mutex_init(&table->philo[count].lock, NULL);
	if (count < table->n_phil - 1)
		table->philo[count].r_fork = &table->philo[count + 1].l_fork;
	else if (table->n_phil == 1)
		table->philo[count].r_fork = &table->philo[count].l_fork;
	else
		table->philo[count].r_fork = &table->philo[0].l_fork;
	return (1);
}

int	ft_init_threads(t_table *table)
{
	int	count;

	count = -1;
	table->time_start = ft_gettime();
	while (++count < table->n_phil)
	{
		ft_init_philo(table, count);
		if (pthread_create(&(table->philo[count].thread_id), \
		NULL, &myphilofunc, &(table->philo[count])) != 0)
			return (EXIT_FAILURE);
		usleep(50);
	}
	count = -1;
	while (++count < table->n_phil)
	{
		if (pthread_join(table->philo[count].thread_id, NULL) != 0)
			return (EXIT_FAILURE);
	}
	return (0);
}
