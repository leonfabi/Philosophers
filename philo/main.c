/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:56:30 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/17 17:27:24 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	mutex;



void	table_status(t_table *table)
{
	printf("N_phil:\t%d\nTime_d:\t%d\nTime_e:\t%d\nTime_s:\t%d\n", table->n_phil, table->time_d, table->time_e, table->time_s);
}

int	main(int argc, char **argv)
{
	int			i;
	int			*res = 0;
	int			value = 0;
	struct timeval	time;
	t_table		table;


	//pthread_mutex_init(&mutex, NULL);
	if (argc != 5)
		return (ft_error_mgmt(MISSING_ARG));
	if (ft_input_check(argc, argv))
		return (EXIT_FAILURE);
	if (ft_init(argc, argv, &table))
		return (EXIT_FAILURE);
	gettimeofday(&time, NULL);
	ft_free(&table);
	return (1);
}
