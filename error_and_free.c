/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:51:29 by avegis            #+#    #+#             */
/*   Updated: 2024/07/29 12:51:40 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t	ft_strlen(const char *str)
{
	size_t	size;

	if (str == NULL || *str == 0)
		return (0);
	size = 0;
	while (*str != 0)
	{
		size++;
		str++;
	}
	return (size);
}

int	join_fail(pthread_t thread)
{
	pthread_detach(thread);
	return (1);
}

int	create_fail(t_rt *rt, int i, pthread_t obs)
{
	int	count;

	count = 0;
	if (pthread_join(obs, NULL) != 0)
		count += join_fail(obs);
	while (i > 0)
	{
		if (pthread_join(rt->philos[i].thread, NULL) != 0)
			count += join_fail(rt->philos[i].thread);
		i--;
	}
	if (count > 0)
	{
		if (count == 1)
			printf("A thread failed to join after failed creation\n");
		if (count > 1)
		{
			printf("%i amount of threads failed to join\n", count);
			printf("after failed thread creation\n");
		}
		cleanse("Detach was used on failed joins\n", rt);
	}
	return (1);
}

int	cleanse(char *str, t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->philos[0].philo_count)
	{
		pthread_mutex_destroy(&rt->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rt->write_lock);
	pthread_mutex_destroy(&rt->eat_lock);
	pthread_mutex_destroy(&rt->death_lock);
	pthread_mutex_destroy(&rt->begin_lock);
	free(rt->forks);
	free(rt->philos);
	if (str != NULL)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	return (1);
}
