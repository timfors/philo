#include "philo.h"

void	fork_delete(void *data)
{
	pthread_mutex_t	*fork;

	fork = (pthread_mutex_t *)data;
	pthread_mutex_destroy(fork);
	free(fork);
}

pthread_mutex_t	*fork_create()
{
	pthread_mutex_t	*res;

	res = m_calloc(sizeof(pthread_mutex_t));
	if (!res)
		return (0);
	if (pthread_mutex_init(res, 0))
	{
		free(res);
		return (0);
	}
	return (res);
}

t_list	*forks_create(int count)
{
	t_list		*res;
	pthread_mutex_t	*fork;
	int		i;

	res = list_create();
	if (!res)
		return (0);
	i = 0;
	while (i < count)
	{
		fork = fork_create();
		if (!fork || !list_add(res, fork))
		{
			list_destroy(&res, fork_delete);
			return (0);
		}
		i++;
	}
	return (res);
}

void	forks_put_on_table(t_philo *philos, t_list *forks)
{
	t_list_el	*current;
	int		i;

	i = 0;
	current = forks->start;
	while (i < forks->size)
	{
		philos[i].fork_l = current->content;
		philos[i].fork_r = current->prev->content;
		i++;
		current = current->next;
	}
}
