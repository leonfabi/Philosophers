/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:45:46 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/13 12:07:46 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

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

struct s_table;

typedef struct s_philo
{
	struct s_table	*table;
	int				state;
	int				id;
	pthread_t		thread_id;
	pthread_t		mon_id;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct timeval	time;
	struct timeval	start_time;
}	t_philo;

typedef struct s_table
{
	int		n_phil;
	int		time_d;
	int		time_e;
	int		time_s;
	int		n_eat;
	int		dead;
	pthread_mutex_t	lock;
	t_philo	*philo;
}	t_table;

int			ft_error_mgmt(int errno);
int			ft_input_check(int argc, char **argv);
long long	ft_atoi(const char *nptr);
int	ft_init(int argc, char **argv, t_table *table);
int	ft_init_threads(t_table *table);
void	ft_free(t_table *table);

#endif