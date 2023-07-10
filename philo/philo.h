/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:45:46 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/10 10:20:42 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <sys/time.h>

# define MISSING_ARG_MSG "Error: Missing arguments\n"
# define NO_NUMBER_MSG "Error: Not a number\n"
# define LIMIT_MSG "Error: Exceeding limits of int\n"
# define NEG_NUMBER_MSG "Error: Negative numbers not allowed\n"
# define PHIL_RANGE_MSG "Error: Philosophers out of range\n"
# define FORK_MSG "has taken a fork\n"
# define EAT_MSG "is eating\n"
# define SLEEP_MSG "is sleeping\n"
# define THINK_MSG "is thinking\n"
# define DEAD_MSG "died\n"
# define MAX_INT 2147483647
# define MIN_INT -2147483648

enum e_state
{
	EAT,
	THINK,
	SLEEP
};

enum e_error
{
	MISSING_ARG,
	NO_NUMBER,
	LIMIT,
	NEG_NUMBER,
	PHIL_RANGE
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

int			ft_error_mgmt(int errno);
int			ft_input_check(int argc, char **argv);
long long	ft_atoi(const char *nptr);
int	ft_init(int argc, char **argv, t_table *table);

#endif