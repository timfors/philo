#include "philo.h"

static void	start_threads(t_logger *logger, t_params params, int philo_count)
{
	pthread_t	*philo_threads;
	t_list		*forks;
	t_philo		*philos;

	philos = philos_create(philo_count, params);
	if (!philos)
		return ;
	forks = forks_create(philo_count);
	if (!forks)
		return ;
	forks_put_on_table(philos, forks);
	philo_threads = m_calloc(philo_count);
	if (!philo_threads)
		return ;
	while (--philo_count >= 0)
		pthread_create(philo_threads + philo_count,
			0, philo_actions, philos + philo_count);
	while (logger->is_work)
		;
	usleep(1000000);
	list_destroy(&forks, fork_delete);
	free(philos);
	free(philo_threads);
	logger_delete(&logger);
}

int	main(int argc , char **argv)
{
	int		philo_count;
	t_params	params;
	t_logger	*logger;
	pthread_t	logger_thread;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo philo_count time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (argc == 5)
		params = params_init(argv[2], argv[3], argv[4], 0);
	else
		params = params_init(argv[2], argv[3], argv[4], argv[5]);
	philo_count = to_num(argv[1]);
	logger = logger_create();
	if (!logger)
	{
		printf("Log Error!\n");
		return (0);
	}
	params.logger = logger;
	pthread_create(&logger_thread, 0, logger_monitor, logger);
	start_threads(logger, params, philo_count);
	while (1);
	return (0);
}
