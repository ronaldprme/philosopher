/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:21:52 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/02/06 14:45:46 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_data *data, int id, char *action)
{
	pthread_mutex_lock(&data->write_lock);
	pthread_mutex_lock(&data->dead_lock);
	pthread_mutex_lock(&data->philo->meal_lock);
	if (!data->dead && data->full == 0)
		printf("%ld %d %s\n", ft_get_time(data), id, action);
	pthread_mutex_unlock(&data->philo->meal_lock);
	pthread_mutex_unlock(&data->dead_lock);
	pthread_mutex_unlock(&data->write_lock);
}

int	ft_time_without_eat(t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->meal_lock);
	time = ft_get_time(philo->data) - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	return (time);
}
