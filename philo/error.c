/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:08:02 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/01/30 00:53:57 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
R = \033[1;31m
G = \033[1;32m
Y = \033[1;33m
B = \033[1;34m
RESET = \033[0m
*/

void	ft_error(t_info *info, t_philo *ph, int flag)
{	
	printf("\033[1;31m");
	if (flag == 1 || flag == 2)
		printf("Error : Wrong number/format of arguments ...\n");
	if (flag == 3)
		printf("Error : Arguments value/s not vaild ...\n");
	if (flag == 4)
	{
		printf("Error : Mem allocation failed ...\n");
		if (ph)
			free(ph);
		if (info)
			free(info);
	}
	if (flag == 5)
	{
		printf("Error : Thread / Mutex lock creation failed ..\n");
		free(ph);
		free(info);
	}
	if (flag == 6)
	{
		pthread_mutex_lock(&info->print_lock);
		printf("Simulation stops as philosopher %d dies ..\n",ph->ph_id);
		pthread_mutex_unlock(&info->print_lock);
		pthread_mutex_destroy(&info->print_lock);
		pthread_mutex_destroy(&ph->r_fork);
		pthread_mutex_destroy(&ph->l_fork);
	}
	printf("\033[0m");
	exit(1);
}

