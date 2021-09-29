#include "philo.h"

t_list	*list_create()
{
	t_list		*res;

	res = m_calloc(sizeof(t_list));
	if (!res)
		return (0);
	if (pthread_mutex_init(&res->mutex, 0))
	{
		free(res);
		return (0);
	}
	return (res);
}

int	list_add(t_list *lst, void *content)
{
	t_list_el	*new_el;
	t_list_el	*last;

	if (!lst)
		return (0);
	new_el = el_create(content);
	if (!new_el)
		return (0);
	pthread_mutex_lock(&lst->mutex);
	if (lst->size == 0)
	{
		lst->start = new_el;
		lst->end = new_el;
	}
	last = lst->end;
	lst->start->prev = new_el;
	lst->end = new_el;
	new_el->next = lst->start;
	pthread_mutex_unlock(&lst->mutex);
	last->next = new_el;
	new_el->prev = last;
	lst->size++;
	return (1);
}

void	list_clear(t_list *lst, void (*del)(void *))
{
	t_list_el	*current;
	t_list_el	*next;

	pthread_mutex_lock(&lst->mutex);
	current = lst->start;
	while (lst->size)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
		lst->size--;
	}
	lst->size = 0;
	lst->start = 0;
	lst->end = 0;
	pthread_mutex_unlock(&lst->mutex);
}

void	list_remove(t_list *lst, t_list_el *el, void (*del)(void *))
{
	t_list_el	*tmp;
	int		i;

	i = 0;
	tmp = lst->start;
	while (i < lst->size)
	{
		if (tmp == el)
		{
			pthread_mutex_lock(&lst->mutex);
			lst->size--;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			if (tmp == lst->start)
				lst->start = tmp->next;
			if (tmp == lst->end)
				lst->end = tmp->prev;
			del(tmp->content);
			free(tmp);
			pthread_mutex_unlock(&lst->mutex);
			return ;
		}
		tmp = tmp->next;
	}
}

void	list_destroy(t_list **lst, void (*del)(void *))
{
	list_clear(*lst, del);
	pthread_mutex_destroy(&(*lst)->mutex);
	free(*lst);
	*lst = 0;
}
