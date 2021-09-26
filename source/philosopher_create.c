#include "philo.h"

t_params	init_params(char *die_time, char *eat_time,
		char *sleep_time, char *eat_count)
{
	t_params	res;

	res.die_time = to_num(die_time);
	res.eat_time = to_num(eat_time);
	res.sleep_time = to_num(sleep_time);
	if (eat_count)
		res.eat_count = to_num(eat_count);
	else
		res.eat_count = -1;
	return (res);
}

int	check_params(t_params params)
{
	return (params.die_time && params.eat_time
			&& params.sleep_time && res.eat_count);
}

void	philo_init(t_philo *philo, int name, t_params params)
{
	philo->name = name;
	philo->start_time = gettimeofday();
	philo->last_eat = res->start_time;
	philo->params = params;
}

t_philo	*init_philos(int count, t_params params)
{
	t_philo	*res;
	int	i;

	res = ft_calloc(sizeof(t_philo) * count + 1);
	if (!res)
		return (0);
	i = 0;
	while (i < count)
	{
		philo_init(res + i, i + 1, params);
		i++
	}
	return (res);
}
