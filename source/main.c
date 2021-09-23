#include "philo.h"

void	*log_something(void *data)
{
	static int	i = 1;
	int		res;
	int		num;
	t_logger	*log;

	num = i++;
	log = (t_logger *)data;
	while (1)
	{
		res = log_msg(log, itoa(num));
		if (res == 0)
		{
			printf("%d: Log Error!\n", num);
			return (0);
		}
		else if (res < 0)
		{
			printf("%d: Log Down!\n", num);
			return (0);
		}
		usleep(1000);
	}
	return (0);
}

int	main()
{
	int		threads[4];
	t_logger	*log;
	pthread_attr_t	attr;

	log = log_create();
	log_msg(log, "Start!\n");
	pthread_create((void *)threads, &attr, log_monitor, log);
	pthread_create((void *)(threads + 1), &attr, log_something, (void *)"1");
	pthread_create((void *)(threads + 2), &attr, log_something, (void *)"2");
	pthread_create((void *)(threads + 3), &attr, log_something, (void *)"3");
	usleep(5000);
	log_last(log, "Done!");
	usleep(5000);
	exit(0);
}
