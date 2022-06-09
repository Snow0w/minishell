/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:59:33 by omanie            #+#    #+#             */
/*   Updated: 2021/10/19 16:05:07 by omanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

char	*ftt_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char) c)
		i++;
	if (c != '\0' && s[i] == '\0')
		return ((void *) 0);
	return ((char *)(s + i));
}

size_t	ftt_strlen(const char *str)
{
	size_t	cnt;

	if (!str)
		return (0);
	cnt = 0;
	while (str[cnt])
		cnt++;
	return (cnt);
}

size_t	ftt_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	if (dstsize == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

char	*buf_clean(char **str, char **buf)
{
	if (*buf)
	{
		free(*buf);
		*buf = (void *) 0;
	}
	if (*str)
	{
		free(*str);
		*str = (void *) 0;
	}
	return ((void *) 0);
}
