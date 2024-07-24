#include "philosophers.h"

static void	init_argv(t_philo *philo, char **argv)
{
	philo->philo_count = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->eat_count = ft_atoi(argv[5]);
	else
		philo->eat_count = -1;
}

// Initialization of philoisophers one by one
void	init_philos(t_rt *rt, t_philo *philos,
		pthread_mutex_t *forks, char **argv)
{
	int count;
	int	i;

	count = ft_atoi(argv[1]);
	i = 0;
	while (i < count)
	{
		init_argv(&philos, argv);
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &rt->write_lock;
		philos[i].death_lock = &rt->death_lock;
		philos[i].eat_lock = &rt->eat_lock;
		philos[i].dead = &rt->dead;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].philo_count - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

// Runtime initialization
void	init_runtime(t_rt *rt, t_philo *philos)
{
	pthread_mutex_init(&rt->death_lock, NULL);
	pthread_mutex_init(&rt->write_lock, NULL);
	pthread_mutex_init(&rt->eat_lock, NULL);
	rt->philos = philos;
	rt->dead = 0;
	return ;
}

// Initialization of forks
void	init_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
