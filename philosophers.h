/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:52:29 by avegis            #+#    #+#             */
/*   Updated: 2024/07/29 12:52:31 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			start_time;
	int				philo_count;
	int				eat_count;
	int				*terminate;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*begin_lock;
}	t_philo;

typedef struct s_rt
{
	pthread_mutex_t	death_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	begin_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				terminate;
}	t_rt;

// Initialization
void	init_runtime(t_rt *rt, t_philo *philos, pthread_mutex_t *forks);
void	init_forks(pthread_mutex_t *forks, int count);
void	init_philos(t_rt *rt, t_philo *philos, char **argv);

// Thread creation and joining
void	single_philo(t_philo *philo);
int		create_threads(t_rt *rt);

// Error and free
int		join_fail(pthread_t thread);
int		create_fail(t_rt *rt, int i, pthread_t obs);
int		cleanse(char *str, t_rt *rt);

// Monitor thread
void	*monitor(void *pointer);
void	print_message(char *str, t_philo *philo);

// philo actions and life
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	*philo_life(void *arg);
int		death_loop(t_philo *philo);

// Utility functions
int		ft_isdigit_str(char *str);
int		ft_atoi(const char *str);
int		precision_usleep(size_t milliseconds);
size_t	get_current_time(void);

#endif
