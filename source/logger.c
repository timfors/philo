#include "philo.h"

void	*logger_monitor(void *data)
{
	t_list		*logs;
	t_logger	*logger;

	logger = (t_logger *)data;
	if (!logger)
		return (0);
	logs = logger->logs;
	while (logger->is_work)
	{
		if (logger->last != logs->end)
		{
			if (!logger->last)
			{
				logger->last = logs->start;
				log_print(logger->last);

			}
			else if (logger->last->next != logs->start)
			{
				logger->last = logger->last->next;
				log_print(logger->last);
			}
		}
	}
	while (logs->end == logger->last)
		;
	log_print(logs->end);
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
	if (!logger)
		return (0);
	if (!logger->is_work)
		return (-1);
	if (!log || !list_add(logger->logs, log))
		return (0);
	return (1);
}

int	logger_last(t_logger *logger, t_log *log)
{
	if (!logger)
		return (0);
	if (!logger->is_work)
		return (-1);
	logger->is_work = 0;
	if (!log || !list_add(logger->logs, log))
		return (0);
	return (1);
}

void	logger_delete(t_logger **logger)
{
	list_destroy(&(*logger)->logs, log_delete);
	free(*logger);
}
