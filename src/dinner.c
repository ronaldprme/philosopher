/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:16:51 by rprocopi          #+#    #+#             */
/*   Updated: 2024/04/19 15:26:46 by rprocopi         ###   ########.fr       */
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
	write_text("is eating", philo);
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

void	philo_think(t_philo *philo)
{
	if (has_philo_died(philo))
		return ;
	write_text("is thinking", philo);
}

void	philo_sleep(t_philo *philo)
{
	if (has_philo_died(philo))
		return ;
	write_text("is sleeping", philo);
	custom_wait(philo->table->time_to_sleep, philo, 2);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = current_time_ms();
	if ((philo->id % 2) == 0 && philo->id != 1)
		usleep(1.5e3);
	while (1)
	{
		philo_think(philo);
		if (!philo_eat(philo))
			break ;
		philo_sleep(philo);
		if (has_philo_died(philo))
			break ;
	}
	return (NULL);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	write_text("has taken a fork", philo);
	usleep(philo->table->time_to_die * 1e3);
	write_text("died", philo);
	return (NULL);
}
