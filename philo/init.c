/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:31:38 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/01/31 03:50:54 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(int ac, char **av )
{
	struct timeval	start;
	t_info			*info;

	gettimeofday(&start, NULL);
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[2]) < 60 || \
		ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60 || \
		ft_atoi(av[1]) < 1)
		ft_error(NULL, NULL, 3);
	info = malloc(sizeof(t_info) * ft_atoi(av[1]));
	info->total_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&info->print_lock, NULL);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) > 1)
			info->max_eats = ft_atoi(av[5]);
		else
			info->max_eats = -1;
	}
	init_philo(info);
}

void	init_philo(t_info *info)
{
	t_philo	*ph;
	int		i;

	i = 0;
	ph = malloc(sizeof(t_philo) * info->total_philo);
	if (!ph)
		ft_error(info, ph, 4);
	while (i < info->total_philo)
	{
		ph[i].ph_id = i + 1;
		ph[i].alive = 1;
		ph[i].meal_eaten = 0;
		ph[i].info = info;
		ph[i].fork = 0;
		gettimeofday(&ph[i].start, NULL);
		pthread_mutex_init(&ph[i].l_fork, NULL);
		pthread_mutex_init(&ph[i].r_fork, NULL);
		if ((i + 1) == info->total_philo)
			ph[i].next = &ph[0];
		else
			ph[i].next = &ph[i + 1];
		i++;
	}
	t_creat(info, ph);
}

void	t_creat(t_info *info, t_philo *ph)
{
	int	result;
	int	result2;
	int	i;

	i = 0;
	while (i < info->total_philo)
	{
		result = pthread_create(&ph[i].thread, NULL, &routine, (void *) &ph[i]);
		if (result != 0)
			ft_error(info, ph, 5);
		i++;
		usleep(300);
	}
	i = 0 ;
	usleep(200);
	while (i < info->total_philo)
	{
		result2 = pthread_join(ph[i].thread, NULL);
		if (result2 != 0)
			ft_error(info, ph, 5);
		usleep(200);
		i++;
	}
}
