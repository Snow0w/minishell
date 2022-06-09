/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:41:54 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:42:15 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <libft.h>
#include <commands.h>
#include <unistd.h>
#include <stdlib.h>
#include <signals.h>
#include <sys/wait.h>

int	no_command_work(t_cmd **cmd)
{
	if (simple_redir_builtin((*cmd)->redirs, get_dup_fd()))
		return (1);
	if (put_fd_back(get_dup_fd()))
		return (1);
	return (0);
}

int	check_minishell_recursive(t_cmd *cmd)
{
	char	*name;
	size_t	len;

	name = (cmd->argv)[0];
	len = ft_strlen(name);
	if (len < 10)
		return (1);
	len = len - 10;
	if (ft_streq(&name[len], "/minishell"))
		return (0);
	return (1);
}

int	minishell_recursive(t_cmd **cmd)
{
	pid_t	pid;
	int		status;

	signals_ignore();
	pid = fork();
	if (pid == -1)
		return (std_func_err());
	if (pid == 0)
		exit(simple_call_one_proc(cmd, 1));
	if (waitpid(pid, &status, 0) == -1)
		return (std_func_err());
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
