/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:56:54 by aelsiddi          #+#    #+#             */
/*   Updated: 2023/03/11 09:30:37 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				philo_pos;
	int				left_fork;
	int				right_fork;
	int				meals;
	int				panic;
	unsigned int	last_eating;
	struct s_table	*table;
}				t_philo;

typedef struct s_table
{
	int						total_num;
	int						meals_to_eat;
	int						*f_state;
	int						*greedy_forks;
	int						stop;
	t_philo					*ph;
	pthread_t				thread[200];
	unsigned int			time_to_die;
	unsigned int			time_to_eat;
	unsigned int			time_to_sleep;
	unsigned int			start_time;
	pthread_mutex_t			forks[200];
	pthread_mutex_t			*p_mutex;
	pthread_mutex_t			*death;
	pthread_mutex_t			*greedy_mutex;
}			t_table;

int				ft_atoi(const char *str);
int				parsing(char **av);
int				ft_isdigit(int n);
int				init_threads(t_table *ph);
int				init(t_table *ph);
int				mutex_init(t_table *ph);
int				start(t_table *ph);
int				greedy_o(t_philo *ph);
int				eat(t_philo *ph);
int				odd(t_philo *ph);
int				even(t_philo *ph);
int				sleep_action(t_philo *ph);
int				ft_usleep(unsigned int time_to_delay, t_philo *ph);
int				check_death(t_philo *ph);
int				greedy_e(t_philo *ph);
void			save(char **av, t_table *ph);
void			ft_putstr_fd(char *s, int fd);
void			ft_bzero(void *dest, size_t len);
void			*ft_calloc(size_t count, size_t size);
void			handle_greedy_philo_eat(t_philo *ph);
void			destroy_free(t_table *ph);
void			init_table(t_philo *ph, int i);
void			print_error(void);
void			*flow(void *arg);
void			print(t_philo *ph, char *state);
unsigned int	time_calc(void);
#endif