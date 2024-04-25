/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:39 by rprocopi          #+#    #+#             */
/*   Updated: 2024/04/25 15:40:44 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	increase_meal_counter(t_philo *philo)
{
	if (philo->table->max_meals != -1)
		philo->n_meals += 1;
}

void	write_text(char *text, t_philo *philo)
{
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	printf("%lld %d %s\n", elapsed_time_ms(philo->table->dinner_start),
		philo->id, text);
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
