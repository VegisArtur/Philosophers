#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct	s_philo
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
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*eat_lock;
}	t_philo;

typedef struct	s_rt
{
	pthread_mutex_t	death_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	eat_lock;
	t_philo			*philos;
	int				dead;
}	t_rt;

// Initialization
void	init_runtime(t_rt *rt, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int count);

// Utility functions
int	ft_atoi(const char *str);
int	ft_usleep(size_t milliseconds);
size_t	get_current_time(void);

#endif