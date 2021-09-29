#include "philo.h"

static	void	philos_monitor(t_philo *philos, int philo_count, t_logger *logger)
{
	int	i;
	int	done_count;
	int	check_res;
	t_log	*log;

	while (1)
	{
		i = -1;
		done_count = 0;
		while (++i < philo_count)
		{
			check_res = philo_check(philos + i);
			if (check_res == 2)
				done_count++;
			else if (check_res == 0)
			{
				log = log_create(get_time(), philos[i].name, "died");
				logger_last(logger, log);
				return;
			}
			if (done_count == philo_count)
				return;
		}
	}
}

static int	start_threads(t_logger *logger, t_params params, int philo_count)
{
	pthread_t	*philo_threads;
	t_list		*forks;
	t_philo		*philos;
	int		i;

	philos = philos_create(philo_count, params);
	forks = forks_create(philo_count);
	philo_threads = m_calloc(philo_count);
	if (!philos || !forks || !philo_threads)
		return (0);
	forks_put_on_table(philos, forks);
	i = -1;
	while (++i < philo_count)
		pthread_create(philo_threads + i,
			0, philo_actions, philos + i);
	philos_monitor(philos, philo_count, logger);
	logger->is_work = 0;
	usleep(1000);
	free(philo_threads);
	free(philos);
	list_destroy(&forks, fork_delete);
	logger_delete(&logger);
	return (1);
}

int	main(int argc , char **argv)
{
	int		philo_count;
	t_params	params;
	pthread_t	logger_thread;
	t_logger	*logger;

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
	params.logger = logger;
	if (!logger || pthread_create(&logger_thread,
			0, logger_monitor, logger)
		|| !start_threads(logger, params, philo_count))
	{
		printf("Error!\n");
		return (0);
	}
	return (0);
}
