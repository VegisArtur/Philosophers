/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:52:42 by avegis            #+#    #+#             */
/*   Updated: 2024/07/29 12:52:43 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	single_philo(t_philo *philo)
{
	while (!death_loop(philo))
	{
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo);
		precision_usleep(philo->time_die);
		pthread_mutex_unlock(philo->r_fork);
		sleeping(philo);
		thinking(philo);
	}
}

// Joining threads for all philos and the observer
static int	join_threads(t_rt *rt, pthread_t obs)
{
	int	i;

	i = 0;
	if (pthread_join(obs, NULL) != 0)
	{
		cleanse("Error joining thread", rt);
		return (1);
	}
	while (i < rt->philos[0].philo_count)
	{
		if (pthread_join(rt->philos[i].thread, NULL) != 0)
		{
			cleanse("Error joining thread", rt);
			return (1);
		}
		i++;
	}
	return (0);
}

// Creating threads for all philos and an observer
int	create_threads(t_rt *rt)
{
	pthread_t	obs;
	int			i;

	if (pthread_create(&obs, NULL, &monitor, rt->philos) != 0)
	{
		cleanse("Error creating thread", rt);
		return (-1);
	}
	i = 0;
	pthread_mutex_lock(&rt->begin_lock);
	while (i < rt->philos[0].philo_count)
	{
		if (pthread_create(&rt->philos[i].thread, NULL, &philo_life,
				&rt->philos[i]) != 0)
		{
			cleanse("Error creating thread", rt);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&rt->begin_lock);
	join_threads(rt, obs);
	return (0);
}
