#include "philosophers.h"

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
		return (1);
	}
	i = 0;
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
	join_threads(rt, obs);
	return (0);
}
