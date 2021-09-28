#include "philo.h"

t_params	params_init(char *die_time, char *eat_time,
		char *sleep_time, char *eat_count)
{
	t_params	res;

	res.die_time = to_num(die_time);
	res.eat_time = to_num(eat_time);
	res.sleep_time = to_num(sleep_time);
	if (eat_count)
		res.eat_count = to_num(eat_count);
	else
		res.eat_count = -1;
	return (res);
}
