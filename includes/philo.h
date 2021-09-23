#ifndef PHILO_H
# define PHILO_H
# define LOG_DELAY 5

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

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
}			t_list;

typedef struct s_logger
{
	t_list	*messages;
	int	is_work;
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
}		t_philo;

t_list		*list_create();
int		list_add(t_list *lst, void *content);
void		list_clear(t_list *lst, void (*del)(void *));
void		list_remove(t_list *lst, t_list_el *el, void (*del)(void *));

t_logger	*log_create();
int		log_msg(t_logger *log, const char *str);
int		log_last(t_logger *log, const char *str);
void		*log_monitor(void *log);

//void		init_philo(int name, t_params params);

int		str_len(char *str);
char		*str_dub(const char *str);
char		*itoa(int num);
void		*m_calloc(int size);
#endif
