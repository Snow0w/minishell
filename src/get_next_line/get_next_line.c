/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:18:40 by omanie            #+#    #+#             */
/*   Updated: 2021/10/19 16:06:09 by omanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

int	n_not_in_stock(char **str, char **buf)
{
	char	*var;

	var = malloc(sizeof(char) * (ftt_strlen(*str) + ftt_strlen(*buf) + 1));
	if (!var)
		return (-1);
	ftt_strlcpy(var, *str, ftt_strlen(*str) + 1);
	ftt_strlcpy(var + ftt_strlen(*str), *buf, ftt_strlen(*buf) + 1);
	free(*str);
	*str = var;
	return (0);
}

int	n_in_stock(char	*ptr_n, char **str, char **buf)
{
	char	*var;

	if (ptr_n == *buf + ftt_strlen(*buf))
		return (n_not_in_stock(str, buf));
	var = malloc(sizeof(char) * (ftt_strlen(*str) + ptr_n - *buf + 2));
	if (!var)
		return (-1);
	ftt_strlcpy(var, *str, ftt_strlen(*str) + 1);
	ftt_strlcpy(var + ftt_strlen(*str), *buf, ptr_n - *buf + 2);
	free(*str);
	*str = var;
	var = malloc(sizeof(char) * (ftt_strlen(*buf) - (ptr_n - *buf)));
	if (!var)
		return (-1);
	ftt_strlcpy(var, ptr_n + 1, (ftt_strlen(*buf) - (ptr_n - *buf)));
	free(*buf);
	*buf = var;
	return (1);
}

int	gnl_append_str(char **str, char **buf, int logic)
{
	char	*ptr;
	int		flag;

	ptr = ftt_strchr((const char *)(*buf), '\n');
	if (ptr)
	{
		flag = n_in_stock(ptr, str, buf);
		if (flag == -1)
			return (-1);
		if (!flag)
		{
			free(*buf);
			*buf = (void *) 0;
		}
		return (1);
	}
	if (n_not_in_stock(str, buf) == -1)
		return (-1);
	if (logic)
	{
		free(*buf);
		*buf = (void *) 0;
	}
	return (0);
}

int	logic(int fd, char **str, char **buf)
{
	int	ret;
	int	point;

	*buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(*buf))
		return (-1);
	ret = read(fd, *buf, BUFFER_SIZE);
	if (ret == -1)
		return (-1);
	(*buf)[ret] = '\0';
	point = 0;
	while (ret && !point)
	{
		point = gnl_append_str(str, buf, 0);
		if (point == -1)
			return (-1);
		if (!point)
		{
			ret = read(fd, *buf, BUFFER_SIZE);
			if (ret == -1)
				return (-1);
			(*buf)[ret] = '\0';
		}
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*buf;
	int			flag;
	int			ret;

	str = (void *) 0;
	flag = 0;
	if (buf)
		flag = gnl_append_str(&str, &buf, 1);
	if (flag == -1)
		return (buf_clean(&str, &buf));
	if (flag == 1)
		return (str);
	ret = logic(fd, &str, &buf);
	if (ret == -1)
		return (buf_clean(&str, &buf));
	if (ret == 0 && str && *str == '\0')
		return (buf_clean(&str, &buf));
	return (str);
}
