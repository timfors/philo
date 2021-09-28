#include "philo.h"

void	philo_init(t_philo *philo, int name, t_params params)
{
	philo->name = name;
	philo->start_time = get_time();
	philo->last_eat = philo->start_time;
	philo->params = params;
}

t_philo	*philos_create(int count, t_params params)
{
	t_philo	*res;
	int	i;

	res = m_calloc(sizeof(t_philo) * count + 1);
	if (!res)
		return (0);
	i = 0;
	while (i < count)
	{
		philo_init(res + i, i + 1, params);
		i++;
	}
	return (res);
}
