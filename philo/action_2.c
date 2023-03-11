/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:22:05 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/03/11 09:49:13 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	sleep_action(t_philo *ph)
{
	if (!check_death(ph))
		return (0);
	print(ph, ": is sleeping ");
	if (!ft_usleep(ph->table->time_to_sleep, ph))
		return (0);
	if (!check_death(ph))
		return (0);
	print(ph, ": is thinking ");
	return (1);
}

void	print(t_philo *ph, char *state)
{
	unsigned int	start_time;

	start_time = ph->table->start_time;
	pthread_mutex_lock(ph->table->death);
	pthread_mutex_lock(ph->table->p_mutex);
	if (!ph->panic && !ph->table->stop
		&& ph->meals != ph->table->meals_to_eat)
	{	
		printf("%d [%d] %s\n", (time_calc() - start_time),
			ph->philo_pos, state);
	}
	pthread_mutex_unlock(ph->table->p_mutex);
	pthread_mutex_unlock(ph->table->death);
}

int	check_death(t_philo *ph)
{
	unsigned int	from_last_meal;

	pthread_mutex_lock(ph->table->death);
	if (ph->table->stop != 0 || ph->meals == ph->table->meals_to_eat)
	{
		ph->panic = 1;
		pthread_mutex_unlock(ph->table->death);
		return (0);
	}
	pthread_mutex_unlock(ph->table->death);
	from_last_meal = time_calc() - ph->last_eating;
	pthread_mutex_lock(ph->table->death);
	if (from_last_meal >= ph->table->time_to_die
		&& ph->table->stop == 0)
	{
		pthread_mutex_unlock(ph->table->death);
		print(ph, ": died");
		pthread_mutex_lock(ph->table->death);
		ph->table->stop = 1;
		ph->panic = 1;
		pthread_mutex_unlock(ph->table->death);
		return (0);
	}
	pthread_mutex_unlock(ph->table->death);
	return (1);
}

void	destroy_free(t_table *info)
{
	int	i;

	i = 0;
	while (i < info->total_num)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(info->p_mutex);
	pthread_mutex_destroy(info->death);
	pthread_mutex_destroy(info->greedy_mutex);
	free(info->ph);
	free(info->p_mutex);
	free(info->death);
	free(info->greedy_mutex);
	free(info->f_state);
	free(info->greedy_forks);
}