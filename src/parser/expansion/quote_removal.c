/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:08:05 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 12:24:46 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>

static int	is_quote_to_remove(const char *s, const int *q, size_t i)
{
	if (s[i] != '\'' && s[i] != '"')
		return (0);
	if (i == 0 && q[i] != 0)
		return (1);
	if (i != 0 && q[i] != q[i - 1])
		return (1);
	return (0);
}

static size_t	len_wo_quotes(const char *s, const int *q)
{
	size_t	ans;
	size_t	i;

	ans = 0;
	i = 0;
	while (s[i])
		if (!is_quote_to_remove(s, q, i++))
			++ans;
	return (ans);
}

static t_word	*create_empty_word(size_t len)
{
	t_word	*ans;

	ans = create_word(NULL);
	if (!ans)
		return (NULL);
	free(ans->s);
	ans->s = malloc(sizeof(*ans->s) * (len + 1));
	ans->q = malloc(sizeof(*ans->q) * len);
	if (!ans->s || ! ans->q)
		return (perror_free_word_null(ans));
	return (ans);
}

static t_word	*remove_quotes_from_word(const t_word *word)
{
	t_word	*ans;
	size_t	i;
	size_t	j;

	ans = create_empty_word(len_wo_quotes(word->s, word->q));
	if (!ans)
		return (NULL);
	i = 0;
	j = 0;
	while (word->s[i])
	{
		if (is_quote_to_remove(word->s, word->q, i))
			++i;
		else
		{
			ans->s[j] = word->s[i];
			ans->q[j++] = word->q[i++];
		}
	}
	ans->s[j] = 0;
	return (ans);
}

/*
	Frees arr
*/
t_word	**remove_quotes(t_word **arr)
{
	t_word	**ans;
	size_t	i;

	i = 0;
	ans = malloc(sizeof(*ans) * (arr_len((void **)arr) + 1));
	if (!ans)
		return (perror_and_null());
	while (arr[i])
	{
		ans[i] = remove_quotes_from_word(arr[i]);
		if (!ans[i])
			return (free_2dim_arr((void **)ans));
		++i;
	}
	ans[i] = NULL;
	return (ans);
}
