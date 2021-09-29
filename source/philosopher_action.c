#include "philo.h"

int	philo_check(t_philo *philo)
{
	t_params	params;

	params = philo->params;
	if (params.eat_count > 0 && philo->dinner_count >= params.eat_count)
		return (2);
	if (get_time() - philo->start_time
		- philo->last_eat > params.die_time
		&& philo->state != 1)
		return (0);
	return (1);
}

static void	philo_eat(t_philo *philo)
{
	t_log		*log;
	t_logger	*logger;

	logger = philo->params.logger;
	if (philo->name % 2)
		pthread_mutex_lock(philo->fork_l);
	else
		pthread_mutex_lock(philo->fork_r);
	log = log_create(get_time(), philo->name, "has taken fork");
	logger_add(logger, log);
	if (philo->name % 2)
		pthread_mutex_lock(philo->fork_r);
	else
		pthread_mutex_lock(philo->fork_l);
	philo->state = 1;
	log = log_create(get_time(), philo->name, "has taken fork");
	logger_add(logger, log);
	log = log_create(get_time(), philo->name, "is eating");
	logger_add(logger, log);
	usleep(philo->params.eat_time * 1000);
	philo->dinner_count++;
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

	philo = (t_philo *)data;
	logger = philo->params.logger;
	usleep((philo->name % 2) *  200);
	philo->start_time = get_time();
	while (logger->is_work)
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
