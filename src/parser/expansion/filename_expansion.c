/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:14:05 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 12:19:30 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

static int	is_pattern(const t_word *word)
{
	size_t	i;

	i = 0;
	while (word->s[i])
	{
		if (word->s[i] == '*' && word->q[i] == 0)
			return (1);
		++i;
	}
	return (0);
}

static int	iterate(const char *pattern, const char *name, size_t *i, size_t *j)
{
	int	ans;

	ans = 0;
	if (pattern[*i] != '*')
	{
		if (pattern[*i] == name[*j])
		{
			++(*i);
			++(*j);
		}
		else
			return (-1);
	}
	else
	{
		if (pattern[*i + 1] == name[*j])
			ans |= pattern_matches(&pattern[*i + 1], &name[*j]);
		if (pattern[*i + 1] == 0)
			ans |= 1;
		++(*j);
	}
	return (ans);
}

int	pattern_matches(const char *pattern, const char *name)
{
	size_t	i;
	size_t	j;
	int		ans;
	int		ret;

	i = 0;
	j = 0;
	ans = 0;
	while (pattern[i] && name[j])
	{
		ret = iterate(pattern, name, &i, &j);
		if (ret == -1)
			return (0);
		ans |= ret;
	}
	if (pattern[i] == 0 && name[j] == 0)
		return (1);
	return (ans);
}

static t_word	**expand_filename(t_word *word)
{
	DIR				*dirp;
	struct dirent	*dir;
	t_word			**ans;

	ans = NULL;
	dirp = open_cwd();
	if (!dirp)
		return (NULL);
	errno = 0;
	dir = readdir(dirp);
	while (dir)
	{
		if (pattern_matches(word->s, dir->d_name) && (dir->d_name[0] != '.' || \
															word->s[0] == '.'))
			ans = append_word(ans, create_word(dir->d_name));
		dir = readdir(dirp);
	}
	if (closedir(dirp) == -1)
		return (perror_and_null());
	if (errno)
		return (perror_free_word_arr_null(ans));
	if (!ans)
		return (word_to_arr(worddup(word)));
	return (ans);
}

t_word	**filename_exp(t_word **words)
{
	size_t	i;
	t_word	**ans;

	ans = malloc(sizeof(*ans));
	if (!ans)
		return (perror_and_null());
	ans[0] = 0;
	i = 0;
	while (words[i])
	{
		if (is_pattern(words[i]))
			ans = concatenate_words(ans, expand_filename(words[i]));
		else
			ans = append_word(ans, worddup(words[i]));
		if (!ans)
			return (NULL);
		++i;
	}
	return (ans);
}
