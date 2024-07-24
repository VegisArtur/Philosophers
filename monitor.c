#include "philosophers.h"

// Print message funtion
void	print_message(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!death_loop(philo))
		printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}

// Checks if the philosopher is dead
int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->eat_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->eat_lock), 1);
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

// Check if any philo died
int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].philo_count)
	{
		if (philosopher_dead(&philos[i], philos[i].time_die))
		{
			print_message("died", &philos[i]);
			pthread_mutex_lock(philos[0].death_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].death_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// Checks if all the philos ate the num_of_meals
int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].eat_count == -1)
		return (0);
	while (i < philos[0].philo_count)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].meals_eaten >= philos[i].eat_count)
			finished_eating++;
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (finished_eating == philos[0].philo_count)
	{
		pthread_mutex_lock(philos[0].death_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].death_lock);
		return (1);
	}
	return (0);
}

// Monitor thread routine
void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (check_if_dead(philos) == 1)
			break ;
		if (check_if_all_ate(philos) == 1)
			break ;
	}
	return (pointer);
}