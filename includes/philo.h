#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sus/time.h>

typedef struct s_list_el
{
	void			*content;
	struct s_list_el	*next;
	struct s_list_el	*prev;
}				t_list_el;

typedef struct s_list
{
	int		size;
	t_list_el	*start;
	t_list_el	*end;
}

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

t_list		*list_create(void *content);
int		list_add(t_list *lst, void *content);
void		list_clear(t_list **lst, void (*del)(void *));
void		list_remove(t_list *lst, t_list_el el, void (*del)(void *));

void	init_philo(int name, t_params params);
