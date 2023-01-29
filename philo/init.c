/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:31:38 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/01/29 23:01:55 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(int ac, char **av )
{
	struct timeval start;
	t_info 			*info;

	gettimeofday(&start,NULL);
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[2]) < 60 || 
		 ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60 || 
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
	while(i < info->total_philo)
	{
		ph[i].ph_id = i + 1;
		ph[i].alive = 1;
		ph[i].meal_eaten = 0;
		ph[i].info = info;
		ph[i].fork = 0;
		gettimeofday(&ph[i].start,NULL);
		// ph[i].thread = malloc(sizeof(pthread_t));
		pthread_mutex_init(&ph[i].l_fork, NULL);
		pthread_mutex_init(&ph[i].r_fork, NULL);
		if ((i + 1) == info->total_philo)
			ph[i].next = &ph[0];
		else
			ph[i].next = &ph[i + 1];
		// printf("philo number %d \n",ph[i].ph_id);
		i++;
	}
	// printf("******************************************************************\n");
	t_creat(info, ph);
}

void*	routine(void *incoming)
{
	t_philo *ph;
	ph = (t_philo *)incoming;
	int last_eat = 0;
	while (1)
	{
		if(ph->meal_eaten == ph->info->max_eats)
			break;
		if (last_eat != ph->ph_id && check_straving(ph, &ph->start) && dead_finder(ph) != 1)
		{
			pthread_mutex_lock(&ph->r_fork);
			pthread_mutex_lock(&ph->l_fork);
			printer(ph, 1);
			printer(ph, 2);
			usleep(ph->info->time_to_eat);
			pthread_mutex_unlock(&ph->l_fork);
			pthread_mutex_unlock(&ph->r_fork);
			printer(ph, 3);
		}
	}
	return 0;
}

void t_creat(t_info *info, t_philo *ph)
{
	int result;
	int result2;
	int i;
	
	i = 0;
	while (i < info->total_philo)
	{
		result = pthread_create(&ph[i].thread,NULL,&routine, (void *) &ph[i]);
		if (result != 0)
			ft_error(info, ph, 5);
		i++;
		usleep(300);
	}
	i = 0 ;
	// printf("**************** threading ******************\n");
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

/*
    In the init_philo function, the ph variable is being allocated memory 
	for info->total_philo philosophers, but the info variable is being
	 allocated memory for only 1 philosopher. This means that ph is trying
	  to access memory that it doesn't have permission to access, which can 
	  cause a segmentation fault.

    In the t_creat function, the variable i is being used in the while loop
	 condition and also in the pthread_join call, but the variable j is being
	  used to increment the loop. This may cause an out of bounds access and 
	  could cause a segmentation fault.

    In the routine function, ph is being casted to t_philo * but it could be 
	pointing to a different struct which can cause a segmentation fault.

    In the t_creat function, result is not being check to ensure that the thread 
	was created successfully. If the thread creation fails, the program will continue
	 to call pthread_join on an invalid thread ID, which can cause a segmentation fault.

You should check for these issues and fix them accordingly. If you continue to have 
issues, please provide more information about the error message you are receiving 
and the state of the program when the segmentation fault occurs.
*/
