/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 03:42:36 by bgohan            #+#    #+#             */
/*   Updated: 2022/04/09 22:41:22 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*ans;

	ans = malloc((n + 1) * sizeof(*ans));
	if (!ans)
		return (NULL);
	i = 0;
	while (s[i] && i < n - 1)
	{
		ans[i] = s[i];
		++i;
	}
	while (i < n)
		ans[i++] = 0;
	return (ans);
}
