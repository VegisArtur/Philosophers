/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:52:09 by avegis            #+#    #+#             */
/*   Updated: 2024/07/29 12:52:10 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_arguments(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Invalid number of arguments!\n", 30);
		write(2, "Arguments are > count, starve, eat, sleep, (lifetime)\n", 55);
		write(2, "Try 5 800 200 200 (7)\n", 23);
		return (1);
	}
	argc = 1;
	while (argv[argc] != NULL)
	{
		if (ft_isdigit_str(argv[argc]) != 1)
		{
			write(2, "Invalid arguments!\n", 20);
			write(2, "All arguments need to be (positive)numbers!\n", 45);
			return (1);
		}
		if (argc < 5 && ft_atoi(argv[argc]) <= 0)
		{
			write(2, "Invalid arguments!\n", 19);
			write(2, "First 4 arguments need to be above 0\n", 38);
		}
		argc++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rt			runtime;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (check_arguments(argc, argv) != 0)
		return (1);
	philos = malloc (sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
		return (1);
	forks = malloc (sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!forks)
	{
		free (philos);
		return (1);
	}
	init_runtime(&runtime, philos, forks);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(&runtime, philos, argv);
	if (create_threads(&runtime) == 1)
		return (1);
	cleanse(NULL, &runtime);
	return (0);
}
