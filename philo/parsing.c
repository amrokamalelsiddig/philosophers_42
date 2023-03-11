/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 08:28:33 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/03/12 00:19:17 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	int_check(char **av)
{
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1 || \
	ft_atoi(av[2]) < 60 || ft_atoi(av[4]) < 60 || ft_atoi(av[3]) < 60)
	{
		print_error();
		return (0);
	}
	if (ft_atoi(av[1]) == 1)
	{
		print_error();
		return (0);
	}
	return (1);
}

int	char_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		print_error();
		return (0);
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
		{
			print_error();
			return (0);
		}
	}
	return (1);
}

int	parsing(char **av)
{
	int	i;

	i = 1;
	while (av && av[i])
	{
		if (char_check(av[i]) == 0)
			return (0);
		i++;
	}
	if (int_check(av) == 0)
		return (0);
	return (1);
}

void	save(char **av, t_table *ph)
{
	ph->total_num = ft_atoi(av[1]);
	ph->time_to_die = ft_atoi(av[2]);
	ph->time_to_eat = ft_atoi(av[3]);
	ph->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
			ph->meals_to_eat = ft_atoi(av[5]);
	else
		ph->meals_to_eat = -1;
}

int	greedy_o(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
	pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
	if (ph->table->greedy_forks[ph->left_fork] == ph->philo_pos
		|| ph->table->greedy_forks[ph->right_fork] == ph->philo_pos)
	{
		pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
		pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
		return (1);
	}
	pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
	return (0);
}
