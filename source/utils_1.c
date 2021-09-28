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

char	*itoa(int num)
{
	char	*res;
	int	size;
	int	tmp;

	tmp = num;
	size = 1;
	while (tmp > 10)
	{
		tmp /= 10;
		size++;
	}
	res = m_calloc(size + 1);
	if (!res)
		return (0);
	while (--size >= 0)
	{
		res[size] = num % 10 + '0';
		num /= 10;
	}
	return (res);
}

char	*str_dub(const char *str)
{
	char	*res;
	int	len_str;

	len_str = str_len((char *)str);
	res = m_calloc(len_str + 1);
	if (!res)
		return (0);
	while (--len_str >= 0)
		res[len_str] = str[len_str];
	return (res);
}

char	*str_concat(char *str1, char *str2, char div)
{
	char	*res;
	int	i;
	int	len1;
	int	len2;

	len1 = str_len(str1);
	len2 = str_len(str2);
	res = m_calloc(len1 + len2 + 2);
	if (!res)
		return (0);
	i = -1;
	while (++i < len1)
		res[i] = str1[i];
	res[i] = div;
	while (++i < len1 + len2 + 1)
		res[i] = str2[i - len1 - 1];
	return (res);
}
