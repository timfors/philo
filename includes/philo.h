#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sus/time.h>

typedef struct s_logger
{
	void	*mut;
	t_list	*message_order;
}		t_logger;

typedef struct s_params
{
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_times;
	t_logger	*logger;

}			t_params;

typedef struct s_philo
{
	int		name;
	int		state;
	int		last_eat;
	int		start_time;
	t_params	params;
	void	*fork_r;
	void	*forl_l;
}		t_philo

void	init_philo(int name, t_params params);
