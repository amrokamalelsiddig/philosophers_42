/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:57:37 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/03/12 00:14:52 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	info;

	info.start_time = time_calc();
	if (ac < 4)
	{
		print_error();
		return (0);
	}
	else if (ac == 5 || ac == 6)
	{
		if (!parsing(av))
			return (0);
		save(av, &info);
		if (!start(&info))
			return (0);
		destroy_free(&info);
	}
	else
	{
		print_error();
		return (0);
	}
	return (0);
}
