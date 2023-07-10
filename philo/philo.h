/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:45:46 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/10 09:10:54 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>

# define MISSING_ARG_MSG "Error: Missing arguments"

enum e_state
{
	EAT,
	THINK,
	SLEEP
};

enum e_error
{
	MISSING_ARG
};

typedef struct s_philo
{
	int		state;
	int		number;
}	t_philo;

typedef struct s_table
{
	int		n_phil;
	int		time_d;
	int		time_e;
	int		time_s;
	int		n_eat;
	t_philo	philo;
}	t_table;

int	ft_error_mgmt(int errno);

#endif