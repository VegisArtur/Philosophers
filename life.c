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
	ft_usleep(philo->time_sleep);
}

// eating function
static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo);
	if (philo->philo_count == 1)
	{
		ft_usleep(philo->time_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo);
	philo->eating = 1;
	print_message("is eating", philo);
	pthread_mutex_lock(philo->eat_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->eat_lock);
	ft_usleep(philo->time_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	death_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->death_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->death_lock);
	return (0);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!death_loop(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (arg);
}
