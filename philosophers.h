#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include "libft/libft.h"

typedef struct	s_philo
{
	pthread_t	thread;
	int			id;
	int			meals_eaten;
}	t_philo;

typedef struct	s_rt
{
	pthread_mutex_t	death_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philo;
	int				death;
}	t_rt;

// Initialization
void	init_runtime(t_rt rt);

#endif