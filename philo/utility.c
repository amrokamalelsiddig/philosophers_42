/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 08:28:41 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/03/11 09:18:38 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

unsigned int	time_calc(void)
{
	struct timeval	time;
	unsigned int	res;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

void 	print_error()
{
	ft_putstr_fd("Error !!!", 2);
}

int	ft_usleep(unsigned int time_to_delay, t_philo *ph)
{
	unsigned int	now_time;

	now_time = time_calc();
	if (!check_death(ph))
		return (0);
	while ((time_calc() - now_time) < (time_to_delay))
	{
		if (!check_death(ph))
			return (0);
		usleep(100);
	}
	return (1);
}

void	handle_greedy_philo_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
	ph->table->greedy_forks[ph->left_fork] = ph->philo_pos;
	pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
	pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
	ph->table->greedy_forks[ph->right_fork] = ph->philo_pos;
	pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
}

int	greedy_e(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->forks[ph->left_fork]);
	pthread_mutex_lock(&ph->table->forks[ph->right_fork]);
	if (ph->table->greedy_forks[ph->left_fork] == ph->philo_pos \
		|| ph->table->greedy_forks[ph->right_fork] == ph->philo_pos)
	{
		pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
		pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&ph->table->forks[ph->right_fork]);
	pthread_mutex_unlock(&ph->table->forks[ph->left_fork]);
	return (0);
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
