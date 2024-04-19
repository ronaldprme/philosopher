/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:26 by rprocopi          #+#    #+#             */
/*   Updated: 2024/04/19 16:59:37 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1e3));
}

long long	elapsed_time_ms(long long start_time)
{
	long long	end_time;

	end_time = current_time_ms();
	return (end_time - start_time);
}

int	custom_wait(int wait_ms, t_philo *philo, int flag)
{
	long long	start_time;

	start_time = current_time_ms();
	while (elapsed_time_ms(start_time) < wait_ms)
	{
		if (has_philo_died(philo))
		{
			if (flag == 1)
			{
				drop_forks(philo);
				return (1);
			}
			if (flag == 2)
				return (1);
		}
		usleep(50);
	}
	return (0);
}

int	has_philo_died(t_philo *philo)
{
	mutex_handle(&philo->table->mtx, LOCK);
	if (philo->table->end)
	{
		mutex_handle(&philo->table->mtx, UNLOCK);
		return (1);
	}
	if (elapsed_time_ms(philo->last_meal) >= philo->table->time_to_die)
	{
		philo->table->end = 1;
		write_text(RED"died"RST, philo);
		mutex_handle(&philo->table->mtx, UNLOCK);
		return (1);
	}
	mutex_handle(&philo->table->mtx, UNLOCK);
	return (0);
}
