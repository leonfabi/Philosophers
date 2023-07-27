/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:56:30 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/27 12:28:41 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	mutex;



void	table_status(t_table *table)
{
	int count = -1;
	// printf("N_phil:\t%d\nTime_d:\t%d\nTime_e:\t%d\nTime_s:\t%d\n", table->n_phil, table->time_d, table->time_e, table->time_s);
	// while (++count < table->n_phil)
	// {
	// 	printf("Philosopher: %d, Left fork: %p, Right fork: %p\n", table->philo[count].id, &table->philo[count].l_fork, table->philo[count].r_fork);
	// }
	// count = -1;
	while (++count < table->n_phil - 1)
	{
		if (table->philo[count].r_fork == &table->philo[count + 1].l_fork)
			printf("Philo %d, Rightfork: %p, Philo %d, Leftfork: %p \n", table->philo[count].id, table->philo[count].r_fork, table->philo[count + 1].id, &table->philo[count + 1].l_fork);
	}
	if (table->philo[count].r_fork == &table->philo[0].l_fork)
		printf("Philo %d, Rightfork: %p, Philo %d, Leftfork: %p \n", table->philo[count].id, table->philo[count].r_fork, table->philo[0].id, &table->philo[0].l_fork);
}

int	main(int argc, char **argv)
{
	int			i;
	int			*res = 0;
	int			value = 0;
	struct timeval	time;
	t_table		table;


	if (argc != 5)
		return (ft_error_mgmt(MISSING_ARG));
	if (ft_input_check(argc, argv))
		return (EXIT_FAILURE);
	if (ft_init_table(argc, argv, &table))
		return (EXIT_FAILURE);
	ft_init_threads(&table);
	// table_status(&table);
	ft_free(&table);
	return (1);
}
