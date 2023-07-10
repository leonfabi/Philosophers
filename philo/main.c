/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:56:30 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/10 10:25:55 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"

pthread_mutex_t	mutex;

void *myThreadFun(void *vargp)
{
	int *value = (int *)vargp;
	int	count = 0;
	while (count < 10000)
	{
		count++;
		*value = *value + 1;
	}
	// printf("Value: %d\n", *value);
	return (value);
}

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
	pthread_t	tid[3];
	t_table		table;


	//pthread_mutex_init(&mutex, NULL);
	if (argc != 5)
		return (ft_error_mgmt(MISSING_ARG));
	if (ft_input_check(argc, argv))
		return (EXIT_FAILURE);
	if (ft_init(argc, argv, &table))
		return (EXIT_FAILURE);
	gettimeofday(&time, NULL);
	printf("%ld ms", time.tv_usec / 1000);
	table_status(&table);
	i = -1;
	while (++i < 3)
	{
		if (pthread_create(&tid[i], NULL, &myThreadFun, (void *)&value) != 0)
			return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < 3)
	{
		if (pthread_join(tid[i], (void **)&res) != 0)
			return (EXIT_FAILURE);
	}
	//pthread_mutex_destroy(&mutex);
	//printf("Value: %d\n", );
	pthread_exit(NULL);
	return (1);
}
