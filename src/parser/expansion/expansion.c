/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:42:07 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:55:15 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>
#include <libft.h>

static char	**expand_str2(t_word **splitted)
{	
	t_word	**wo_quotes;
	char	**ans;

	wo_quotes = remove_quotes(splitted);
	free_word_arr(splitted);
	if (!wo_quotes)
		return (NULL);
	splitted = filename_exp(wo_quotes);
	free_word_arr(wo_quotes);
	if (!splitted)
		return (NULL);
	ans = words_to_strings(splitted);
	return (ans);
}

static char	**expand_str(const char *s)
{
	t_word	*word;
	int		ret;
	t_word	**splitted;

	word = create_word(s);
	if (!word)
		return (NULL);
	ret = param_exp(&word);
	if (ret == -1)
		return (free_word(word));
	if (ret == 0)
		splitted = word_to_arr(word);
	else
	{
		splitted = split_words(word);
		free_word(word);
	}
	if (!splitted)
		return (NULL);
	return (expand_str2(splitted));
}

static char	**expand_arr(char **arr)
{
	char	**ans;
	char	**expanded;
	size_t	i;

	ans = malloc(sizeof(*ans));
	if (!ans)
		return (perror_and_null());
	ans[0] = 0;
	i = 0;
	while (arr[i])
	{
		expanded = expand_str(arr[i]);
		if (!expanded)
			return (free_2dim_arr((void **)ans));
		ans = (char **)concatenate_arrays((void **)ans, (void **)expanded);
		if (!ans)
			return (free_2dim_arr((void **)expanded));
		free(expanded);
		++i;
	}
	return (ans);
}

/*
	Returns
	1 if error occured
	0 otherwise
*/
int	expand_pipeline(t_cmd **pipeline)
{
	size_t	i;
	char	**new_arr;

	i = 0;
	while (pipeline[i])
	{
		new_arr = expand_arr(pipeline[i]->argv);
		if (!new_arr)
			return (1);
		free_2dim_arr((void **)pipeline[i]->argv);
		pipeline[i]->argv = new_arr;
		if (expand_redirs(pipeline[i]->redirs) == 1)
			return (1);
		++i;
	}
	return (0);
}

/*
	Returns
	1 if error occured
	0 otherwise
*/
int	expand_redirs(t_redir **redirs)
{
	size_t	i;
	char	**expanded_arg;

	i = 0;
	while (redirs[i])
	{
		if (redirs[i]->type == HERE_DOC)
		{
			++i;
			continue ;
		}
		expanded_arg = expand_str(redirs[i]->arg);
		if (!expanded_arg)
			return (1);
		if (expanded_arg[1])
		{
			free_2dim_arr((void **)expanded_arg);
			return (ambiguous_redir(redirs[i]->arg));
		}
		free(redirs[i]->arg);
		redirs[i]->arg = expanded_arg[0];
		free(expanded_arg);
		++i;
	}
	return (0);
}
