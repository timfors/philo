#include "philo.h"

t_log	*log_create(int timestamp, int name, const char *str)
{
	t_log	*log;
	int	str_size;

	log = m_calloc(sizeof(t_log));
	if (!log)
		return (0);
	log->timestamp = timestamp;
	log->name = name;
	str_size = str_len((char *)str);
	log->msg = m_calloc(str_size + 1);
	if (!log->msg)
	{
		free(log);
		return (0);
	}
	while (--str_size >= 0)
		log->msg[str_size] = str[str_size];
	return (log);
}

void	log_delete(void *data)
{
	t_log	*log;

	log = (t_log *)data;
	free(log->msg);
	free(log);
}
