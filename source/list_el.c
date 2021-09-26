#inlcude "philo.h"

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
