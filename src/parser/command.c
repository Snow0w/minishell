/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 22:20:35 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:54:09 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>
#include <stdlib.h>

static size_t	count_redirs(char **splitted)
{
	size_t	ans;
	size_t	i;

	ans = 0;
	i = 0;
	while (splitted[i] && !is_control_operator(splitted[i]))
		if (is_redir_operator(splitted[i++]))
			++ans;
	return (ans);
}

static size_t	count_args(char **splitted)
{
	size_t	ans;
	size_t	i;

	ans = 0;
	i = 0;
	while (splitted[i] && !is_control_operator(splitted[i]))
		if (!is_redir_operator(splitted[i++]))
			++ans;
	ans -= count_redirs(splitted);
	return (ans);
}

static char	**get_argv(char **splitted, size_t *ret_len)
{
	char	**argv;
	size_t	cur_arg;
	size_t	i;

	argv = malloc(sizeof(*argv) * (count_args(splitted) + 1));
	if (!argv)
		return (perror_and_null());
	cur_arg = 0;
	i = 0;
	while (splitted[i] && !is_control_operator(splitted[i]))
	{
		if (!is_redir_operator(splitted[i]))
		{
			argv[cur_arg] = ft_strdup(splitted[i++]);
			if (!argv[cur_arg++])
				return (free_2dim_arr((void **)argv));
		}
		else
			i += 2;
	}
	argv[cur_arg] = 0;
	*ret_len = i;
	return (argv);
}

static t_redir	**get_redirs(char **splitted)
{
	t_redir	**redirs;
	char	**redirs_arr;
	size_t	cur_redir;
	size_t	i;

	redirs_arr = malloc(sizeof(*redirs_arr) * (2 * count_redirs(splitted) + 1));
	if (!redirs_arr)
		return (perror_and_null());
	cur_redir = 0;
	i = 0;
	while (splitted[i] && !is_control_operator(splitted[i]))
	{
		if (is_redir_operator(splitted[i]))
		{
			redirs_arr[cur_redir++] = splitted[i++];
			redirs_arr[cur_redir++] = splitted[i++];
		}
		else
			++i;
	}
	redirs_arr[cur_redir] = 0;
	redirs = parse_redirs(redirs_arr, NULL);
	free(redirs_arr);
	return (redirs);
}

/*
	Returns
	1 if error occured
	0 otherwise
*/
t_cmd	*parse_command(char **splitted, size_t *ret_len)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (perror_and_null());
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->argv = get_argv(splitted, ret_len);
	if (!cmd->argv)
		return (free_cmd(cmd));
	cmd->redirs = get_redirs(splitted);
	if (!cmd->redirs)
		return (free_cmd(cmd));
	return (cmd);
}
