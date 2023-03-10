/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:08:02 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/03/10 23:05:51 by aelsiddi         ###   ########.fr       */
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

void free_it(t_philo *ph, t_info *info)
{
	int i;
	int z;
	
	i = 0;
 	z = info->total_philo;  
	while(i < z)
	{
		free(&ph[i]);
		i++;
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
		// free(ph->info);
	}
	free_it(ph,info);
	printf("\033[0m");
	exit(1);
}

