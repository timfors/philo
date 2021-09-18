#include "philo.h"

t_list_el	*el_create(void *content)
{
	t_list_el	*res;

	res = m_calloc(sizeof(t_list_el));
	if (!res)
		return (0);
	res->content = content;
	res->next = res;
	res->prev = res;
	return (res);
}

t_list	*list_create()
{
	t_list		*res;

	res = m_calloc(sizeof(t_list));
	if (!res)
		return (0);
	return (res);
}

int	list_add(t_list *lst, void *content)
{
	t_list_el	*new_el;

	if (!lst)
		return (0);
	new_el = el_create(content);
	if (!new_el)
		return (0);
	if (lst->size == 0)
	{
		lst->start = new_el;
		lst->end = new_el;
	}
	else if (lst->size == 1)
	{
		lst->start->next = new_el;
		new_el->prev = lst->start;
	}
	new_el->prev = lst->end;
	new_el->next = lst->start;
	lst->start->prev = new_el;
	lst->end->next = new_el;
	lst->end = new_el;
	lst->size++;
	return (1);
}

void	list_clear(t_list *lst, void (*del)(void *))
{
	t_list_el	*current;
	t_list_el	*next;

	current = lst->start;
	while (lst->size--)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	lst->size = 0;
	lst->start = 0;
	lst->end = 0;
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
			lst->size--;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			if (tmp == lst->start)
				lst->start = tmp->next;
			if (tmp == lst->end)
				lst->end = tmp->prev;
			del(tmp->content);
			free(tmp);
			return ;

		}
		tmp = tmp->next;
	}
}
