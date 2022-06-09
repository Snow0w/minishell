/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:29:55 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:54:15 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>
#include <stdlib.h>

static int	is_pipeline_end(const char *token)
{
	return (is_logical_operator(token) || \
			ft_streq(token, "(") || ft_streq(token, ")"));
}

static int	is_pipe(const char *s)
{
	return (ft_streq(s, "|"));
}

static size_t	count_cmds(char **splitted)
{
	size_t	i;
	size_t	ans;

	i = 0;
	ans = 1;
	while (splitted[i] && !is_pipeline_end(splitted[i]))
		if (is_pipe(splitted[i++]))
			++ans;
	return (ans);
}

t_cmd	**parse_pipeline(char **splitted, size_t *ret_len)
{
	t_cmd	**cmds;
	size_t	cur_cmd;
	size_t	len;
	size_t	i;

	cmds = malloc(sizeof(*cmds) * (count_cmds(splitted) + 1));
	if (!cmds)
		return (perror_and_null());
	cur_cmd = 0;
	i = 0;
	while (splitted[i] && !is_pipeline_end(splitted[i]))
	{
		if (is_pipe(splitted[i]))
		{
			++i;
			continue ;
		}
		cmds[cur_cmd] = parse_command(&splitted[i], &len);
		if (!cmds[cur_cmd++])
			return (free_2dim_arr((void **)cmds));
		i += len;
	}
	cmds[cur_cmd] = 0;
	*ret_len = i;
	return (cmds);
}
