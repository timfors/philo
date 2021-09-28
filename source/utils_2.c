#include "philo.h"

int	to_num(char *str)
{
	int	res;
	int	prev;
	int	i;

	i = 0;
	res = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = res;
		res = res * 10 + str[i] - '0';
		if (prev > res)
			return (0);
		i++;
	}
	return (res);
}

void	empty(void *data)
{
	(void)data;
}
