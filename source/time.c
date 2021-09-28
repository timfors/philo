#include "philo.h"

int	get_time()
{
	static struct timeval	tv_1;
	static int		is_inited = 0;
	struct timeval		tv_2;

	if (!is_inited)
	{
		gettimeofday(&tv_1, 0);
		is_inited = 1;
	}
	gettimeofday(&tv_2, 0);
	return ((tv_2.tv_sec - tv_1.tv_sec) * 1000
		+ (tv_2.tv_usec - tv_1.tv_usec) / 1000);
}
