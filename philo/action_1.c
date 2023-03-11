/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:08:02 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/03/11 09:48:19 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	access_forks(t_philo *ph, int flag)
{
	ph->table->f_state[ph->right_fork] = ph->philo_pos;
	ph->table->f_state[ph->left_fork] = ph->philo_pos;
	if (flag == 1)
	{
		pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
		pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
	}
	else if (flag == 2)
	{
		pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
		pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
	}
	if (!check_death(ph))
		return (0);
	print(ph, ": has taken a fork ");
	print(ph, ": has taken a fork ");
	print(ph, ": is eating ");
	ph->last_eating = time_calc();
	if (!ft_usleep(ph->table->time_to_eat, ph))
		return (0);
	ph->meals++;
	return (1);
}

void	drop_forks(t_philo *ph)
{
	handle_greedy_philo_eat(ph);
	pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
	ph->table->f_state[ph->left_fork] = 0;
	pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
	pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
	ph->table->f_state[ph->right_fork] = 0;
	pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
}

int	even(t_philo *ph)
{
	if (!check_death(ph))
		return (0);
	if (!greedy_o(ph))
	{
		pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
		pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
		if (ph->table->f_state[ph->right_fork] == 0
			&& ph->table->f_state[ph->left_fork] == 0)
		{
			if (!access_forks(ph, 1))
				return (0);
			drop_forks(ph);
			if (!sleep_action(ph))
				return (0);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
			pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
			if (!check_death(ph))
				return (0);
		}
	}
	return (1);
}

int	odd(t_philo *ph)
{
	if (!check_death(ph))
		return (0);
	if (!greedy_e(ph))
	{
		pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
		pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
		if (ph->table->f_state[ph->right_fork] == 0
			&& ph->table->f_state[ph->left_fork] == 0)
		{
			if (!access_forks(ph, 2))
				return (0);
			drop_forks(ph);
			if (!sleep_action(ph))
				return (0);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
			pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
			if (!check_death(ph))
				return (0);
		}
	}
	return (1);
}

int	eat(t_philo *ph)
{
	if (ph->philo_pos % 2 == 0)
	{
		if (even(ph) == 0)
			return (0);
	}
	else
	{
		if (odd(ph) == 0)
			return (0);
	}
	return (1);
}