/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:33:25 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 12:02:22 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>

/*
	Frees words
*/
char	**words_to_strings(t_word **words)
{
	char	**ans;
	size_t	i;

	ans = malloc(sizeof(*ans) * (arr_len((void **)words) + 1));
	if (!ans)
		return (perror_and_null());
	i = 0;
	while (words[i])
	{
		ans[i] = ft_strdup(words[i]->s);
		if (!ans[i])
		{
			free_2dim_arr((void **)ans);
			return (free_word_arr(words));
		}
		++i;
	}
	ans[i] = 0;
	free_word_arr(words);
	return (ans);
}
