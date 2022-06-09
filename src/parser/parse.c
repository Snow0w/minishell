/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:01:51 by bgohan            #+#    #+#             */
/*   Updated: 2022/04/29 18:32:58 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>
#include <libft.h>

t_cmdtree	*parse(char *s)
{
	char		**splitted;
	t_cmdtree	*ans;
	int			*quotes;

	quotes = get_quoting(s);
	if (!quotes)
		return (NULL);
	splitted = split_on_tokens(s, quotes);
	free(quotes);
	if (!splitted)
		return (NULL);
	ans = NULL;
	if (validate(splitted) == 1)
		return (free_2dim_arr((void **)splitted));
	ans = arr_to_tree(splitted, NULL);
	free_2dim_arr((void **)splitted);
	return (ans);
}
