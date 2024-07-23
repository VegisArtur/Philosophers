#include "philosophers.h"

static int  check_arguments(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_printf("Invalid number of arguments!\n");
		ft_printf("Arguments are >>> count, starve, eat, sleep, (lifetime)\n");
		return (1);
	}
	argc = 1;
	while (argv[argc] != NULL)
	{
		if (ft_isdigit_str(argv[argc]) != 1)
		{
			ft_printf("Invalid arguments!\n");
			ft_printf("All arguments need to be numbers!\n");
			return (1);
		}
		if (argc < 5 && ft_atoi(argv[argc]) <= 0)
		{
			ft_printf("Invalid arguments!\n");
			ft_printf("Argument %d need to be above 0\n", argc);
			return (1);
		}
		argc++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_rt	runtime;
	t_philo	philos[200];

	if (check_arguments(argc, argv) != 0)
		return (1);
	init_runtime(runtime);
	return (0);
}
