#include "philosophers.h"

static int  check_arguments(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Invalid number of arguments!\n", 30);
		write(2, "Arguments are >>> count, starve, eat, sleep, (lifetime)\n", 57);
		return (1);
	}
	argc = 1;
	while (argv[argc] != NULL)
	{
		if (ft_isdigit_str(argv[argc]) != 1)
		{
			write(2, "Invalid arguments!\n", 20);
			write(2, "All arguments need to be numbers!\n", 35);
			return (1);
		}
		if (argc < 5 && ft_atoi(argv[argc]) <= 0)
		{
			write(2, "Invalid arguments!\n", 19);
			write(2, "Argument %d need to be above 0\n", 32); // when replaced from printf, I need to remake errors
			return (1);
		}
		argc++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_rt			runtime;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if (check_arguments(argc, argv) != 0)
		return (1);
	init_runtime(&runtime, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &runtime, forks, argv);
	return (0);
}
