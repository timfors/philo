#include "philo.h"

void	*log_monitor(void *data)
{
	t_list		*messages;
	t_logger	*logger;

	logger = (t_logger *)data;
	if (!logger)
		return (0);
	messages = logger->messages;
	while (logger->is_work)
	{
		if (messages->size > 0)
		{
			printf("%s\n", (char *)messages->start->content);
			list_remove(messages, messages->start, free);
		}
	}
	if (messages->size > 0)
	{
		printf("%s\n", (char *)messages->start->content);
		list_remove(messages, messages->start, free);
	}
	return (0);
}

t_logger	*log_create()
{
	t_logger	*res;

	res = m_calloc(sizeof(t_logger));
	if (!res)
		return (0);
	res->messages = list_create();
	if (!res->messages)
		return (0);
	res->is_work = 1;
	return (res);
}

int	log_msg(t_logger *logger, const char *str)
{
	char	*new_str;

	new_str = str_dub(str);
	if (!logger->is_work)
		return (-1);
	if (!new_str)
		return (0);
	if (!list_add(logger->messages, new_str))
		return (0);
	return (1);
}

int	log_last(t_logger *logger, const char *str)
{
	char	*new_str;

	if (!logger->is_work)
		return (-1);
	list_clear(logger->messages, free);
	new_str = str_dub(str);
	if (!new_str)
		return (0);
	if (!list_add(logger->messages, new_str))
		return (0);
	logger->is_work = 0;
	return (1);
}
