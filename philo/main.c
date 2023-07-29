/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:56:30 by fkrug             #+#    #+#             */
/*   Updated: 2023/07/29 14:07:22 by fkrug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc != 5 && argc != 6)
		return (ft_error_mgmt(MISSING_ARG));
	if (ft_input_check(argc, argv))
		return (EXIT_FAILURE);
	if (ft_init_table(argc, argv, &table))
		return (EXIT_FAILURE);
	ft_init_threads(&table);
	ft_free(&table);
	return (1);
}
