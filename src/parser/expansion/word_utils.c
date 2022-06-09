/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 07:58:25 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 12:04:28 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>

t_word	*create_word(const char *s)
{
	t_word	*word;

	word = malloc(sizeof(*word));
	if (!word)
		return (perror_and_null());
	word->s = NULL;
	word->q = NULL;
	if (s)
	{
		word->s = ft_strdup(s);
		if (!word->s)
			return (free_word(word));
		word->q = get_quoting(word->s);
		if (!word->q)
			return (free_word(word));
	}
	else
	{
		word->s = malloc(sizeof(*word->s));
		if (!word->s)
			return (perror_free_word_null(word));
		word->s[0] = 0;
	}
	return (word);
}

t_word	**word_to_arr(t_word *word)
{
	t_word	**arr;

	arr = malloc(sizeof(*arr) * 2);
	if (!arr)
		return (perror_and_null());
	arr[0] = word;
	arr[1] = 0;
	return (arr);
}

/*
	Frees word
*/
t_word	*append_str(t_word *word, const char *s, const int *q)
{
	t_word	*new;
	size_t	len;

	new = malloc(sizeof(*new));
	if (!new)
		return (perror_free_word_null(word));
	len = ft_strlen(word->s) + ft_strlen(s);
	new->s = malloc(sizeof(*new->s) * (len + 1));
	new->q = malloc(sizeof(*new->q) * (len));
	if (!new->s || !new->q)
	{
		free_word(new);
		return (perror_free_word_null(word));
	}
	ft_strlcpy(new->s, word->s, len + 1);
	ft_strlcat(new->s, s, len + 1);
	ft_memcpy(new->q, word->q, sizeof(*new->q) * ft_strlen(word->s));
	ft_memcpy(&new->q[ft_strlen(word->s)], q, sizeof(*q) * ft_strlen(s));
	free_word(word);
	return (new);
}

t_word	*wordndup(const t_word *word, size_t n)
{
	t_word	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (perror_and_null());
	new->s = ft_strndup(word->s, n);
	if (!new->s)
	{
		free(new);
		return (NULL);
	}
	new->q = malloc(sizeof(*new->q) * n);
	if (!new->q)
		return (perror_free_word_null(new));
	ft_memcpy(new->q, word->q, sizeof(*new->q) * n);
	return (new);
}

t_word	*worddup(const t_word *word)
{
	t_word	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (perror_and_null());
	new->s = ft_strdup(word->s);
	if (!new->s)
	{
		free(new);
		return (NULL);
	}
	new->q = malloc(sizeof(*new->q) * (ft_strlen(word->s)));
	if (!new->q)
		return (perror_free_word_null(new));
	ft_memcpy(new->q, word->q, sizeof(*new->q) * ft_strlen(word->s));
	return (new);
}
