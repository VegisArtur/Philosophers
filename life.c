#include "philosophers.h"

// thinking function
static void	thinking(t_philo *philo)
{
	print_message("is thinking", philo);
}

// sleeping function
static void	sleeping(t_philo *philo)
{
	print_message("is sleeping", philo);
	precision_usleep(philo->time_sleep);
}

// eating function
static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo);
	philo->eating = 1;
	print_message("is eating", philo);
	pthread_mutex_lock(philo->eat_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->eat_lock);
	precision_usleep(philo->time_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

// Function to check if the philosopher is dead or not
int	death_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	if (*philo->terminate == 1)
		return (pthread_mutex_unlock(philo->death_lock), 1);
	pthread_mutex_unlock(philo->death_lock);
	return (0);
}

// Function that loops the life of a philosopher
void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precision_usleep(1);
	if (philo->philo_count == 1)
		while (!death_loop(philo))
		{
			pthread_mutex_lock(philo->r_fork);
			print_message("has taken a fork", philo);
			precision_usleep(philo->time_die);
			pthread_mutex_unlock(philo->r_fork);
			sleeping(philo);
			thinking(philo);
		}
	else
		while (!death_loop(philo))
		{
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
	return (arg);
}
