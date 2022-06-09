/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:05:38 by bgohan            #+#    #+#             */
/*   Updated: 2022/04/27 17:26:05 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

void	*free_redir(t_redir *redir)
{
	if (!redir)
		return (NULL);
	if (redir->arg)
		free(redir->arg);
	free(redir);
	return (NULL);
}

void	*free_word(t_word *word)
{
	if (!word)
		return (NULL);
	if (word->s)
		free(word->s);
	if (word->q)
		free(word->q);
	free(word);
	return (NULL);
}

void	*free_word_arr(t_word **words)
{
	size_t	i;

	i = 0;
	if (!words)
		return (NULL);
	while (words[i])
		free_word(words[i++]);
	free(words);
	return (NULL);
}
