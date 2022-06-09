/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:14:31 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 12:00:22 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>

static size_t	calc_token_len(const char *s, const int *quotes)
{
	size_t	i;

	i = 0;
	if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		return (0);
	while (s[i] && (quotes[i] || (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')))
		++i;
	return (i);
}

static size_t	count_tokens(const char *s, const int *quotes)
{
	size_t	ans;
	size_t	i;
	size_t	word_len;

	ans = 0;
	i = 0;
	while (s[i])
	{
		word_len = calc_token_len(&s[i], &quotes[i]);
		if (word_len == 0)
			++i;
		else
		{
			++ans;
			i += word_len;
		}
	}
	return (ans);
}

t_word	**split_words(const t_word *word)
{
	t_word	**ans;
	size_t	word_len;
	size_t	cur;
	size_t	i;

	ans = malloc(sizeof(*ans) * (count_tokens(word->s, word->q) + 1));
	if (!ans)
		return (perror_and_null());
	i = 0;
	cur = 0;
	while (word->s[i])
	{
		word_len = calc_token_len(&word->s[i], &word->q[i]);
		if (word_len == 0)
			++i;
		else
		{
			ans[cur] = wordndup(word, word_len + 1);
			if (!ans[cur++])
				return (free_word_arr(ans));
			i += word_len;
		}
	}
	ans[cur] = 0;
	return (ans);
}
