/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:16:12 by rprocopi          #+#    #+#             */
/*   Updated: 2024/04/19 17:14:08 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (printf(RED"Invalid number of arguments!\n"RST), 1);
	if (ac >= 5)
	{
		parse_input(&table, av);
		init_table(&table);
		init_threads(&table);
		end_simulation(&table);
	}
	else
		return (printf(RED"Invalid number of arguments!\n"RST), 1);
	return (0);
}
