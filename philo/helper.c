/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:58:59 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/01/31 03:53:50 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char	*str)
{
	unsigned int	num;
	int				sing;

	num = 0;
	sing = 1;
	while (*str == ' ' || (*str >= 19 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sing = -sing;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (num > 2147483648 && sing == -1)
		ft_error(NULL, NULL, 2);
	if ((num > 2147483647 && sing == 1)
		|| (*str || (str[0] == '+' && !str[1]) || (str[0] == '-' && !str[1])))
		ft_error(NULL, NULL, 2);
	str = NULL;
	return (num * sing);
}

int	ft_isdigit(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[i++][j])
	{
		if (av[i][j] >= 48 && av[i][j] <= 57)
			j++;
		else
			return (0);
	}
	return (1);
}

long	curr_time(struct timeval *start)
{
	struct timeval	end;
	long			counter;

	gettimeofday(&end, NULL);
	counter = (((end.tv_sec - start->tv_sec) * 1000) + \
	((end.tv_usec - start->tv_usec) / 1000));
	return (counter);
}

int	check_straving(t_philo *ph, struct timeval *start)
{
	struct timeval	end;
	long			counter;

	gettimeofday(&end, NULL);
	counter = (((end.tv_sec - start->tv_sec) * 1000) + \
	((end.tv_usec - start->tv_usec) / 1000));
	if (counter < ph->info->time_to_die)
		return (1);
	else
	{
		ph->alive = 0;
		flow(ph, 5);
		ft_error(ph->info, ph, 6);
		return (0);
	}	
}

int	check_pulse(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->info->total_philo)
	{
		if (ph[i].alive == 0)
			i++;
		else
			return (0);
	}
	return (1);
}
