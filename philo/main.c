/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:15:43 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/02/19 16:21:07 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int ac, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments!\n");
		return (0);
	}
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Error\n");
				return (0);
			}
		}
		if (ft_atoi(argv[i]) <= 0)
			return (0);
	}
	return (1);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philo == 1)
	{
		handle_one_philo(philo);
		return (arg);
	}
	while (ft_dead(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (arg);
}

int	main(int ac, char **argv)
{
	t_data	data;
	int		i;

	if (!check_args(ac, argv))
		return (0);
	ft_init_argvs(ac, argv, &data);
	init_mutexes(&data);
	data.philo = malloc(sizeof(t_philo) * data.number_of_philo);
	if (!data.philo)
		return (0);
	i = -1;
	init_forks(&data);
	while (++i < data.number_of_philo)
	{
		init_philo(&data.philo[i], &data, i);
		pthread_create(&data.philo[i].ph, NULL, \
		(void *)ft_routine, &data.philo[i]);
	}
	i = 0;
	while (!is_anyone_dead(&data) && (!is_everyone_satisfied(&data)))
		usleep(500);
	while (i < data.number_of_philo)
		pthread_join(data.philo[i++].ph, NULL);
	ft_quit(&data);
	return (0);
}
