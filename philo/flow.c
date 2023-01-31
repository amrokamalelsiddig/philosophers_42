/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:22:05 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/01/31 03:52:42 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	flow(t_philo *ph, int flag)
{
	pthread_mutex_lock(&ph->info->print_lock);
	printf("%ld", curr_time(&ph->start));
	printf(" ");
	printf("%d", ph->ph_id);
	if (flag == 1)
		printf (" has taken a fork\n");
	if (flag == 2)
	{
		printf(" is eating now\n");
		ph->last_meal = curr_time(&ph->start);
	}
	if (flag == 3)
	{
		printf(" is sleeping\n");
		usleep(ph->info->time_to_sleep);
	}
	if (flag == 4)
		printf(" is thinking\n");
	if (flag == 5)
	{
		printf(" is dead\n");
		pthread_mutex_destroy(&ph->info->print_lock);
		exit(0);
	}
	pthread_mutex_unlock(&ph->info->print_lock);
}

void*	routine(void *incoming)
{
	t_philo	*ph;
	int		last_eat;

	ph = (t_philo *)incoming;
	last_eat = 0;
	while (1)
	{
		if (last_eat != ph->ph_id && check_straving(ph, &ph->start) != 0)
		{	
			pthread_mutex_lock(&ph->r_fork);
			pthread_mutex_lock(&ph->l_fork);
			flow(ph, 1);
			flow(ph, 2);
			usleep(ph->info->time_to_eat);
			pthread_mutex_unlock(&ph->l_fork);
			pthread_mutex_unlock(&ph->r_fork);
			flow(ph, 3);
		}
	}
	return (0);
}
