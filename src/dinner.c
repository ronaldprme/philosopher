/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:16:51 by rprocopi          #+#    #+#             */
/*   Updated: 2024/04/23 17:09:03 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_eat(t_philo *philo)
{
	take_forks(philo);
	if (has_philo_died(philo))
	{
		drop_forks(philo);
		return (0);
	}
	increase_meal_counter(philo);
	write_text(M"is eating"RST, philo);
	if (custom_wait(philo->table->time_to_eat, philo, 1))
		return (0);
	if (philo->n_meals == philo->table->max_meals)
	{
		drop_forks(philo); 
		return (0);
	}
	philo->last_meal = current_time_ms();
	drop_forks(philo);
	return (1);
}

int	philo_think(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;
	if (has_philo_died(philo))
		return (0);
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat - t_sleep;
	if (t_think < 0)
		t_think = 0;
	write_text(B"is thinking"RST, philo);
	custom_wait(t_think * 0.42, philo, 2);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (has_philo_died(philo))
		return (0);
	write_text(G"is sleeping"RST, philo);
	custom_wait(philo->table->time_to_sleep, philo, 2);
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	philo->last_meal = current_time_ms();
	if ((philo->id % 2) == 0 && philo->id != 1)
		usleep(1.5e3); //evitar deadlock
	while (1)
	{
		if (!philo_think(philo))
			break ;		
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
	}
	return (NULL);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	write_text(Y"has taken a fork"RST, philo);
	usleep(philo->table->time_to_die * 1e3);
	write_text(RED"died"RST, philo);
	return (NULL);
}
