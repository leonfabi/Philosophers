/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:45:46 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/31 15:52:55 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

enum e_state
{
	EAT,
	THINK,
	SLEEP,
	FORK,
};

enum e_error
{
	MISSING_ARG,
	NO_NUMBER,
	LIMIT,
	NEG_NUMBER,
	PHIL_RANGE,
	MIN_TIME
};

struct	s_table;

typedef struct s_philo
{
	struct s_table	*table;
	int				state;
	int				id;
	int				times_ate;
	int				max_eat;
	int				died;
	pthread_t		thread_id;
	pthread_t		mon_id;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	lock;
	double			time_to_die;
	__uint64_t		start_t;
}	t_philo;

typedef struct s_table
{
	int				n_phil;
	int				time_d;
	int				time_e;
	int				time_s;
	int				n_eat;
	int				n_full;
	int				dead;
	int				start;
	double			time_start;
	pthread_mutex_t	full;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_t		monitor;
	t_philo			*philo;
}	t_table;

int			ft_error_mgmt(int errno);
int			ft_input_check(int argc, char **argv);
void		ft_init_philo(t_table *table, int count);
long long	ft_atoi(const char *nptr);
int			ft_init(int argc, char **argv, t_table *table);
int			ft_init_table(int argc, char **argv, t_table *table);
int			ft_init_threads(t_table *table);
void		ft_free(t_table *table);
void		ft_sleep(__uint64_t ms);
__uint64_t	ft_gettime(void);
void		ft_print_state(t_philo *philo);
void		ft_action(t_philo *philo);
void		ft_philo_dead(t_table *table, int count);
void		ft_check_death(t_table *table, int count);
void		ft_full_behave(t_table *table, int count);
int			ft_input_test(int argc, char **argv);
#endif
