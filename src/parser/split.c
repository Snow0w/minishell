/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:31:53 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:54:42 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>

static int	is_metachar(char c)
{
	return (c == '|' || c == '&' || \
			c == '(' || c == ')' || \
				c == '<' || c == '>');
}

static size_t	calc_token_len(const char *s, const int *quotes)
{
	size_t	i;

	i = 0;
	if (quotes[0] == 0 && (s[0] == ' ' || s[0] == '\t'))
		return (0);
	if (ft_strncmp(s, "||", 2) == 0 || ft_strncmp(s, "&&", 2) == 0 || \
		ft_strncmp(s, ">>", 2) == 0 || ft_strncmp(s, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(s, ">", 1) == 0 || ft_strncmp(s, "<", 1) == 0 || \
		ft_strncmp(s, "(", 1) == 0 || ft_strncmp(s, ")", 1) == 0 || \
		ft_strncmp(s, "|", 1) == 0 || ft_strncmp(s, "&", 1) == 0)
		return (1);
	while (s[i] && (quotes[i] || \
					!(is_metachar(s[i]) || s[i] == ' ' || s[i] == '\t')))
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

char	**split_on_tokens(const char *line, const int *quotes)
{
	char	**ans;
	size_t	word_len;
	size_t	cur;
	size_t	i;

	ans = malloc(sizeof(*ans) * (count_tokens(line, quotes) + 1));
	if (!ans)
		return (perror_and_null());
	i = 0;
	cur = 0;
	while (line[i])
	{
		word_len = calc_token_len(&line[i], &quotes[i]);
		if (word_len == 0)
			++i;
		else
		{
			ans[cur] = ft_strndup(&line[i], word_len + 1);
			if (!ans[cur++])
				return (free_2dim_arr((void **)ans));
			i += word_len;
		}
	}
	ans[cur] = 0;
	return (ans);
}
