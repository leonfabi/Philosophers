/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_states.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:15:07 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/25 09:28:30 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_action(void *vargp)
{
	t_philo *philo;

	philo = (t_philo *)vargp;
	philo->state = THINK;
	ft_print_state(philo);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	philo->state = FORK;
	ft_print_state(philo);
	philo->state = EAT;
	ft_print_state(philo);
	pthread_mutex_lock(&philo->lock);
	philo->start_t = ft_gettime();
	pthread_mutex_unlock(&philo->lock);
	ft_sleep(philo->table->time_e);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	philo->state = SLEEP;
	ft_print_state(philo);
	ft_sleep(philo->table->time_s);
}
