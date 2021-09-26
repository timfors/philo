#include "philo.h"

void	*log_something(void *data)
{
	static int	i = 1;
	int		res;
	int		num = i++;
	char		*str;
	t_logger	*log;

	log = (t_logger *)data;
	printf("NUM %d is cheaking log state %d\n", num, log->is_work);
	while (log->is_work)
	{
		str = itoa(num);
		res = log_msg(log, str);
		free(str);
		if (res == 0)
		{
			printf("%d: Log Error!\n", num);
			return (0);
		}
		usleep(1000000);
	}
	return (0);
}

int	main()
{
	pthread_t	threads[4];
	t_logger	*log;

	log = log_create();
	if (!log)
	{
		printf("Log Error!\n");
		exit(0);
	}
	log_msg(log, "Start!\n");
	pthread_create(threads, 0, log_monitor, log);
	pthread_create(threads + 1, 0, log_something, log);
	pthread_create(threads + 2, 0, log_something, log);
	pthread_create(threads + 3, 0, log_something, log);
	usleep(5000000);
	log_last(log, "Done!");
	usleep(100);
	exit(0);
}
