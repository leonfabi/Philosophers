/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_states.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:15:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/27 16:39:58 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->l_fork);
		philo->state = FORK;
		ft_print_state(philo);
		pthread_mutex_lock(philo->r_fork);
		ft_print_state(philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		philo->state = FORK;
		ft_print_state(philo);
		pthread_mutex_lock(&philo->l_fork);
		ft_print_state(philo);
	}
}

void	ft_eat(t_philo *philo)
{
	philo->state = EAT;
	if (philo->max_eat != -1)
		philo->times_ate += 1;
	// printf("Philo %d ate %d times\n", philo->id, philo->times_ate);
	pthread_mutex_lock(&philo->lock);
	philo->start_t = ft_gettime();
	pthread_mutex_unlock(&philo->lock);
	ft_print_state(philo);
	ft_sleep(philo->table->time_e);
}

void	ft_action(void *vargp)
{
	t_philo *philo;

	philo = (t_philo *)vargp;
	philo->state = THINK;
	ft_print_state(philo);
	if (philo->times_ate < philo->max_eat)
	{
		ft_take_fork(philo);
		ft_eat(philo);
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		if (philo->times_ate == philo->max_eat)
		{
			pthread_mutex_lock(&philo->table->full);
			philo->table->n_full += 1;
			pthread_mutex_unlock(&philo->table->full);
		}
	}
	philo->state = SLEEP;
	ft_print_state(philo);
	ft_sleep(philo->table->time_s);
}
