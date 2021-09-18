#include "philo.h"

void	*m_calloc(int size)
{
	char	*res;
	int	i;

	res = malloc(size);
	if (!res)
		return (0);
	i = 0;
	while (i < size)
		res[i++] = 0;
       return (res);	
}

int	str_len(char *str)
{
	int	size;

	if (!str)
		return (0);
	size = 0;
	while (str[size])
		size++;
	return (size);
}

char	*str_dub(const char *str)
{
	char	*res;
	int	len_str;

	len_str = str_len(str);
	res = m_calloc(len_str + 1);
	if (!res)
		return (0);
	while (--len_str >= 0)
		res[len_str] = str[len_str];
	return (res);
}
