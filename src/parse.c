/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:17 by rprocopi          #+#    #+#             */
/*   Updated: 2024/04/24 17:29:35 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_valid_input(char *str)
{
	int	c;

	c = 0;
	while (is_space(str[c]) && str[c])
		c++;
	if ((str[c] == '+' || str[c] == '-') && str[c])
	{
		if (str[c] == '-')
		error_exit ("Feed only positive values");
		c++;
	}
	while (str[c])
	{
		if (!is_digit(str[c]))
			error_exit("The input is not a correct digit");
		c++;
	}
	return (1);
}

int	ft_atol(char *str)
{
	int		c;
	long	ret;

	c = 0;
	ret = 0;
	if (!is_valid_input(str))
		return (0);
	while (is_space(str[c]))
		c++;
	if (str[c] == '+')
		c++;
	while (is_digit(str[c]))
	{
		ret = ret * 10 + (str[c] - '0');
		if (ret >= INT_MAX || ret <= INT_MIN)
			error_exit("INT_MAX is the limit");
		c++;
	}
	return (ret);
}

void	parse_input(t_table *table, char **av)
{
	table->n_philos = ft_atol(av[1]);
	if (table->n_philos > PHILO_MAX)
	{
		printf(RED"Max philos are %d\n"
			G"make fclean and re-make with PHILO_MAX=nbr to change it\n"RST,
			PHILO_MAX);
		exit(EXIT_FAILURE);
	}
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		table->max_meals = ft_atol(av[5]);
	else
		table->max_meals = -1;
}
