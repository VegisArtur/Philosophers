#include "philosophers.h"
#include <limits.h>

size_t	ft_strlen(const char *str)
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

int	ft_isdigit(unsigned char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isdigit_str(char *str)
{
	while (*str != 0)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

// converts a numerical string to int
int	ft_atoi(const char *str)
{
	long long	count;
	int			pos;

	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	pos = 1;
	if (*str == '-')
		pos *= -1;
	if (*str == '+' || *str == '-')
		str++;
	count = 0;
	while (*str != 0 && ft_isdigit(*str))
	{
		count = count * 10 + (*str - '0');
		if (count < 0)
		{
			if (pos == 1)
				return ((int)LONG_MAX);
			return ((int)LONG_MIN);
		}
		str++;
	}
	return ((int)(count * pos));
}

// helper function to make sure nothing interrupts the philo program
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

// Returns the current time in milliseconds
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
