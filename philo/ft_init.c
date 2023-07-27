/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:40:01 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/27 12:15:13 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_table(int argc, char **argv, t_table *table)
{
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->n_phil);
	if (!table->philo)
	{
		free(table->philo);
		table->philo = NULL;
		return (EXIT_FAILURE);
	}
	pthread_mutex_init(&table->lock, NULL);
	pthread_mutex_init(&table->write, NULL);
	table->dead = 0;
	table->n_eat = -1;
	return (ft_init(argc, argv, table));
	// return (ft_init_threads(table));
}

int	ft_init(int argc, char **argv, t_table *table)
{
	int			count;
	long long	number;

	count = 0;
	number = 0;
	while (++count < argc)
	{
		number = ft_atoi(argv[count]);
		if (number > MAX_INT)
			return (ft_error_mgmt(LIMIT));
		else if (number < 0)
			return (ft_error_mgmt(NEG_NUMBER));
		else if (count == 1 && number < 1)
			return (ft_error_mgmt(PHIL_RANGE));
		else if (count == 1)
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
