#include "philo.h"

void	log_monitor(t_logger *logger)
{
	t_list	*messages;

	if (!logger)
		return ;

	messages = logger->messages;
	while (logger->is_work)
	{
		if (messages->size)
		{
			printf("%s\n", messages->start->content);
			list_remove(messages, messages->start);
		}
		usleep(LOG_DELAY);
	}
	if (messages->size)
	{
		printf("%s\n", messages->start->content);
		list_remove(messages, messages->start);
	}
}

int	log_msg(t_logger *logger, const char *str)
{
	char	*new_str;

	new_str = str_dub(str);
	if (!str)
		return (0);
	if (!list_add(logger->messages, new_str))
		return (0);
	return (1);
}

int	log_last(t_logger *logger, const char *str)
{
	list_clear()
}
