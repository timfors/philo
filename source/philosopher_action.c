#include "philo.h"

static void	*philo_check_death(void *data)
{
	t_philo		*philo;
	t_logger	*logger;
	t_params	params;
	t_log		*log;

	philo = (t_philo *)data;
	logger = philo->params.logger;
	params = philo->params;
	while (logger->is_work && params.eat_count)
	{
		if (get_time() - philo->start_time
			- philo->last_eat > params.die_time
			&& philo->state != 1)
		{
			log = log_create(get_time(),
				philo->name, "died");
			logger_last(logger, log);
		}
	}
	return (0);
}

static void	philo_eat(t_philo *philo)
{
	t_log		*log;
	t_logger	*logger;

	logger = philo->params.logger;
	if (philo->name % 2)
		pthread_mutex_lock(philo->fork_r);
	else
		pthread_mutex_lock(philo->fork_l);
	log = log_create(get_time() - philo->start_time, philo->name, "has taken fork");
	logger_add(logger, log);
	if (philo->name % 2)
		pthread_mutex_lock(philo->fork_l);
	else
		pthread_mutex_lock(philo->fork_r);
	philo->state = 1;
	log = log_create(get_time(), philo->name, "has taken fork");
	logger_add(logger, log);
	log = log_create(get_time(), philo->name, "is eating");
	logger_add(logger, log);
	usleep(philo->params.eat_time * 1000);
	if (philo->params.eat_count > 0)
		philo->params.eat_count--;
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

static void	philo_sleep(t_philo *philo)
{
	t_log		*log;
	t_logger	*logger;

	logger = philo->params.logger;
	philo->state= 2;
	log = log_create(get_time(), philo->name, "is sleeping");
	logger_add(logger, log);
	usleep(philo->params.sleep_time * 1000);
}

static void	philo_think(t_philo *philo)
{
	t_log		*log;
	t_logger	*logger;

	logger = philo->params.logger;
	philo->state = 3;
	log = log_create(get_time(), philo->name, "is thinking");
	logger_add(logger, log);
}

void	*philo_actions(void *data)
{
	t_philo		*philo;
	t_logger	*logger;
	pthread_t	death_monitor;

	philo = (t_philo *)data;
	logger = philo->params.logger;
	philo->start_time = get_time();
	pthread_create(&death_monitor, 0, philo_check_death, data);
	while (logger->is_work && philo->params.eat_count)
	{
		if (philo->state == 0 || philo->state == 3)
			philo_eat(philo);
		else if (philo->state == 1)
			philo_sleep(philo);
		else if (philo->state == 2)
			philo_think(philo);
	}
	return (0);
}
