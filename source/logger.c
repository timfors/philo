#include "philo.h"

void	*logger_monitor(void *data)
{
	t_list		*logs;
	t_logger	*logger;
	t_log		*log;

	logger = (t_logger *)data;
	if (!logger)
		return (0);
	logs = logger->logs;
	while (logger->is_work)
	{
		if (logs->size > 0)
		{
			log = (t_log *)logs->start->content;
			printf("%d %d %s\n", log->timestamp, log->name, log->msg);
			list_remove(logs, logs->start, log_delete);
		}
	}
	while (logs->size == 0)
		;
	log = (t_log *)logs->end->content;
	printf("%d %d %s\n", log->timestamp, log->name, log->msg);
	list_clear(logs, log_delete);
	return (0);
}

t_logger	*logger_create()
{
	t_logger	*res;

	res = m_calloc(sizeof(t_logger));
	if (!res)
		return (0);
	res->logs = list_create();
	if (!res->logs)
		return (0);
	res->is_work = 1;
	return (res);
}

int	logger_add(t_logger *logger, t_log *log)
{
	if (!logger->is_work)
		return (-1);
	if (!log || !list_add(logger->logs, log))
		return (0);
	return (1);
}

int	logger_last(t_logger *logger, t_log *log)
{
	if (!logger->is_work)
		return (-1);
	logger->is_work = 0;
	//list_clear(logger->logs, log_delete);
	if (!log || !list_add(logger->logs, log))
		return (0);
	return (1);
}

void	logger_delete(t_logger **logger)
{
	list_destroy(&(*logger)->logs, log_delete);
	free(*logger);
}
