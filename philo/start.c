/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 08:28:38 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/03/12 00:19:49 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start(t_table *info)
{
	int	i;

	i = 0;
	info->stop = 0;
	init(info);
	if (!mutex_init(info))
		return (0);
	while (i < info->total_num)
	{
		info->ph[i].table = info;
		init_table(&info->ph[i], i);
		i++;
	}
	if (!init_threads(info))
		return (0);
	return (1);
}

int	init(t_table *info)
{
	info->ph = malloc(sizeof(t_philo) * info->total_num);
	info->p_mutex = malloc(sizeof(pthread_mutex_t));
	info->greedy_forks = ft_calloc(sizeof(int), info->total_num);
	info->f_state = ft_calloc(sizeof(int), info->total_num);
	info->greedy_mutex = malloc(sizeof(pthread_mutex_t));
	info->death = malloc(sizeof(pthread_mutex_t));
	if (!info->p_mutex || !info->greedy_mutex || !info->ph \
		|| !info->greedy_forks || !info->death || \
		!info->f_state)
	{
		print_error();
		return (0);
	}
	return (1);
}

int	init_threads(t_table *info)
{
	int			i;
	int			holder;
	int			holder2;

	i = 0;
	while (i < info->total_num)
	{
		holder = pthread_create(&info->thread[i], NULL, flow, \
		(void *)&info->ph[i]);
		if (holder != 0)
			print_error();
		usleep(100);
		i++;
	}
	i = 0;
	while (i < info->total_num)
	{
		holder2 = pthread_join(info->thread[i], NULL);
		if (holder2 != 0)
			print_error();
		i++;
	}
	return (1);
}

int	mutex_init(t_table *info)
{
	int	i;

	i = 0;
	while (i < info->total_num)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			print_error();
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(info->p_mutex, NULL) != 0
		|| pthread_mutex_init(info->death, NULL) != 0
		|| pthread_mutex_init(info->greedy_mutex, NULL) != 0)
	{
		print_error();
		return (0);
	}
	return (1);
}

void	init_table(t_philo *ph, int i)
{
	ph->right_fork = (i + 1) % ph->table->total_num;
	ph->left_fork = i;
	ph->meals = 0;
	ph->panic = 0;
	ph->philo_pos = i + 1;
}
