/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:56:54 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/01/29 23:24:30 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#define B = "\033[1;34m"
#define R = "\033[1;31m"
#define Y = "\033[1;33m"
#define G = "\033[1;32m"
#define REST = "\033[0m"


typedef struct s_info
{
	int 				total_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eats;
	pthread_mutex_t		print_lock;
}	t_info;

typedef struct s_philo
{
	int 			ph_id;
	int 			alive;
	int				meal_eaten;
	int 			fork; 
	pthread_t 		thread;
	struct timeval 	start;
	long 			last_meal;	
	struct s_info	*info;
	pthread_mutex_t l_fork;
	pthread_mutex_t r_fork;
	struct s_philo	*next;
}	t_philo;

//********** helper.c **************//
int		ft_isdigit(char **av);
int		ft_atoi(const char	*str);
long	curr_time(struct timeval *start);
void	printer(t_philo *ph, int  flag);
int		check_straving(t_philo *ph, struct timeval *start);
int		dead_finder(t_philo *ph);

//********** error.c **************//
void	ft_error(t_info *info, t_philo *ph, int flag);

//**********  init.c **************//
void	init(int ac, char **av );
void	init_philo(t_info *info);
void	t_creat(t_info *info, t_philo *ph);

//********* flow *****************//
void*	routine(void *incoming);
void printer(t_philo *ph, int  flag);

#endif