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
	int		state;
	pthread_mutex_t	mutex;
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
	int		eat_count;
	t_logger	*logger;

}			t_params;

typedef struct s_philo
{
	int		name;
	int		state;
	int		last_eat;
	int		start_time;
	t_params	params;
	pthread_mutex	*fork_r;
	pthread_mutex	*forl_l;
}		t_philo;

t_list_el	*el_create(void *content);

t_list		*list_create();
int		list_add(t_list *lst, void *content);
void		list_clear(t_list *lst, void (*del)(void *));
void		list_remove(t_list *lst, t_list_el *el, void (*del)(void *));
void		list_destroy(t_list **lst, void(*del)(void *));

t_logger	*log_create();
int		log_msg(t_logger *log, int timestamp, int name, const char *action);
int		log_last(t_logger *log, const char *str);
void		*log_monitor(void *log);

void		fork_delete(void *data);
pthread_mutex	*fork_create();
t_list		*forks_create(int count);
void		forks_put_on_table(t_philo *philos, t_list *forks);

//void		init_philo(int name, t_params params);

int		str_len(char *str);
char		*str_dub(const char *str);
char		*itoa(int num);
void		*m_calloc(int size);
int		to_num(char *str);
#endif
