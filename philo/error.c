/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:08:02 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/02/02 18:42:10 by aelsiddi         ###   ########.fr       */
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
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*a;

	i = 0;
	a = (unsigned char *)b;
	while (i < len)
	{
		*(a + i) = c;
		i++;
	}
	return (a);
}

void free_it(t_philo *ph, t_info *info, int flag)
{
	int i;

	i = 0;
	if (flag == 1)
	{
		while(i < info->total_philo)
		{
			free(&ph[i]);
			i++;
		}	
	}
	else if (flag == 2)
	{
		i = info->total_philo;
		free(info);
	}
}

void	ft_error(t_info *info, t_philo *ph, int flag)
{	
	(void)ph;
	(void)info;
	printf("\033[1;31m");
	if (flag == 1 || flag == 2)
		printf("Error : Wrong number/format of arguments ...\n");
	if (flag == 3)
		printf("Error : Arguments value/s not vaild ...\n");
	if (flag == 4)
		printf("Error : Mem allocation failed ...\n");
	if (flag == 5)
		printf("Error : Thread / Mutex lock creation failed ..\n");
	if (flag == 6)
	{
		// while(ph->next != NULL)
		// {
		// 	free(ph->info);
		// 	ph = ph->next;
		// }	
	}
	// free(ph->info);
	// free_it(ph,info, 1);
	printf("\033[0m");
	exit(1);
}

