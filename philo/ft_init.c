/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:40:01 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/29 13:19:42 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_table *table, int count)
{
	table->philo[count].id = count + 1;
	table->philo[count].state = THINK;
	table->philo[count].time_to_die = table->time_d;
	table->philo[count].table = table;
	table->philo[count].died = 0;
	table->philo[count].max_eat = table->n_eat;
	table->philo[count].start_t = 0;
	if (table->philo[count].max_eat == -1)
		table->philo[count].times_ate = -2;
	else
		table->philo[count].times_ate = 0;
	pthread_mutex_init(&table->philo[count].l_fork, NULL);
	pthread_mutex_init(&table->philo[count].lock, NULL);
	if (count < table->n_phil - 1)
		table->philo[count].r_fork = &table->philo[count + 1].l_fork;
	else if (table->n_phil == 1)
		table->philo[count].r_fork = &table->philo[count].l_fork;
	else
		table->philo[count].r_fork = &table->philo[0].l_fork;
}

int	ft_init_table(int argc, char **argv, t_table *table)
{
	int	count;

	count = -1;
	if (ft_init(argc, argv, table))
		return (EXIT_FAILURE);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->n_phil);
	if (!table->philo)
	{
		free(table->philo);
		table->philo = NULL;
		return (EXIT_FAILURE);
	}
	pthread_mutex_init(&table->lock, NULL);
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->full, NULL);
	table->dead = 0;
	table->start = 0;
	table->n_full = 0;
	while (++count < table->n_phil)
		ft_init_philo(table, count);
	return (EXIT_SUCCESS);
}
int	ft_input_check(int argc, char **argv)
{
	int			count;
	long long	number;

	count = 0;
	number = 0;
	while (++count < argc)
	{
		number = ft_atoi(argv[count]);
		if (number > 2147483647)
			return (ft_error_mgmt(LIMIT));
		else if (number < 0)
			return (ft_error_mgmt(NEG_NUMBER));
	}
	return (EXIT_SUCCESS);
}

int	ft_init(int argc, char **argv, t_table *table)
{
	int			count;
	long long	number;

	count = 0;
	number = 0;
	if (ft_input_check(argc, argv))
		return (EXIT_FAILURE);
	table->n_eat = -1;
	while (++count < argc)
	{
		number = ft_atoi(argv[count]);
		if (count == 1)
			table->n_phil = (int)number;
		else if (count == 2)
			table->time_d = (int)number;
		else if (count == 3)
			table->time_e = (int)number;
		else if (count == 4)
			table->time_s = (int)number;
		else if (count == 5)
			table->n_eat = (int)number;
	}
	return (EXIT_SUCCESS);
}
