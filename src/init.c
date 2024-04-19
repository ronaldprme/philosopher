/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:08 by rprocopi          #+#    #+#             */
/*   Updated: 2024/04/19 15:25:30 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_table(t_table *table)
{
	table->end = 0;
	table->dinner_start = current_time_ms();
	table->philos = safe_malloc(table->n_philos * sizeof(t_philo));
	table->forks = safe_malloc(table->n_philos * sizeof(t_fork));
	safe_mutex_handle(&table->mtx, INIT);
	safe_mutex_handle(&table->log, INIT);
	init_forks(table);
	init_philos(table);
}

void	init_forks(t_table *table)
{
	int	c;

	c = 0;
	while (c < table->n_philos)
	{
		mutex_handle(&table->forks[c].mtx, INIT);
		table->forks[c].id = c;
		c++;
	}
}

void	init_philos(t_table *table)
{
	int	c;

	c = 0;
	while (c < table->n_philos)
	{
		table->philos[c].id = c + 1;
		table->philos[c].last_meal = table->dinner_start;
		table->philos[c].n_meals = 0;
		table->philos[c].is_dead = 0;
		table->philos[c].left_fork = &table->forks[c];
		table->philos[c].right_fork = &table->forks[(c + 1) % table->n_philos];
		table->philos[c].table = table;
		c++;
	}
}

void	init_threads(t_table *table)
{
	int	c;

	c = 0;
	while (c < table->n_philos)
	{
		if (table->n_philos == 1)
		{
			if (pthread_create(&table->philos[c].philo, NULL, 
					one_philo, (void *)&table->philos[c]) != 0)
			{
				printf("Error creating philo thread!\n");
				return ;
			}
		}
		else
		{
			if (pthread_create(&table->philos[c].philo, NULL, 
					philosopher_routine, (void *)&table->philos[c]) != 0)
			{
				printf("Error creating philo thread!\n");
				return ;
			}
		}
		c++;
	}
}
