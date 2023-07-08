/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:56:30 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/08 12:52:52 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t	mutex;

void *myThreadFun(void *vargp)
{
	int *value = (int *)vargp;
	int	count = 0;
	while (count < 100)
	{
		count++;
		*value = *value + 1;
	}
	// printf("Value: %d\n", *value);
	return (NULL);
}

int	main(void)
{
	int			i;
	int			value = 0;
	pthread_t	tid[3];


	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < 3)
	{
		pthread_mutex_lock(&mutex);
		if (pthread_create(&tid[i], NULL, &myThreadFun, (void *)&value) != 0)
			return (EXIT_FAILURE);
		pthread_mutex_unlock(&mutex);
		// pthread_join(tid[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	printf("Value: %d\n", value);
	pthread_exit(NULL);
	return (1);
}
