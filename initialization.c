/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:51:46 by avegis            #+#    #+#             */
/*   Updated: 2024/07/29 12:51:52 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// initialization of arguments into philosophers
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
void	init_philos(t_rt *rt, t_philo *philos, char **argv)
{
	int	count;
	int	i;

	count = ft_atoi(argv[1]);
	i = 0;
	while (i < count)
	{
		init_argv(&philos[i], argv);
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &rt->write_lock;
		philos[i].death_lock = &rt->death_lock;
		philos[i].eat_lock = &rt->eat_lock;
		philos[i].begin_lock = &rt->begin_lock;
		philos[i].terminate = &rt->terminate;
		philos[i].l_fork = &rt->forks[i];
		if (i == 0)
			philos[i].r_fork = &rt->forks[count - 1];
		else
			philos[i].r_fork = &rt->forks[i - 1];
		i++;
	}
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

// Runtime initialization
void	init_runtime(t_rt *rt, t_philo *philos, pthread_mutex_t *forks)
{
	pthread_mutex_init(&rt->death_lock, NULL);
	pthread_mutex_init(&rt->write_lock, NULL);
	pthread_mutex_init(&rt->eat_lock, NULL);
	pthread_mutex_init(&rt->begin_lock, NULL);
	rt->philos = philos;
	rt->forks = forks;
	rt->terminate = 0;
	return ;
}
