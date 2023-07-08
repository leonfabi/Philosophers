/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:56:30 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/03 15:56:22 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int g = 10;

void *myThreadFun(void *vargp)
{
	int *myid = (int *)vargp;
	static int s = 0;

	char command[256];
	char str[12];

	++s;
	printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, g);
}

int	main(void)
{
	int			i;
	pthread_t	tid;

	i = -1;
	while (++i < 3)
		pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
	pthread_exit(NULL);
	return (1);
}
