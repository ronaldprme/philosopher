/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:16:32 by rprocopi          #+#    #+#             */
/*   Updated: 2024/04/25 12:30:52 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	join_threads(t_table *table)
{
	int	c;

	c = 0;
	while (c < table->n_philos)
	{
		if (pthread_join(table->philos[c].philo, NULL) < 0)
			printf("Thread join error\n");
		c++;
	}
}

void	destroy_mutexes(t_table *table)
{
	int	c;

	c = 0;
	safe_mutex_handle(&table->write_mutex, DESTROY);
	while (c < table->n_philos)
	{
		safe_mutex_handle(&table->forks[c].mtx, DESTROY);
		c++;
	}
}

void	end_simulation(t_table *table)
{
	join_threads(table);
	destroy_mutexes(table);
	free(table->philos);
	free(table->forks);
}

void	error_exit(const char *error)
{
	printf(RED">> %s <<\n"RST, error);
	exit(EXIT_FAILURE);
}
