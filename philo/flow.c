/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:58:59 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/03/11 09:52:45 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*flow(void *incoming)
{
	t_philo	*philo;

	philo = (t_philo *)incoming;
	philo->last_eating = time_calc();
	while (philo->meals != philo->table->meals_to_eat && !philo->panic)
	{
		pthread_mutex_lock(philo->table->death);
		if (!philo->table->stop)
		{
			pthread_mutex_unlock(philo->table->death);
			if (!eat(philo))
				return (NULL);
		}
		else
		{
			pthread_mutex_unlock(philo->table->death);
			return (NULL);
		}
	}
	return (incoming);
}