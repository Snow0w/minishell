/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:41:55 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:42:15 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <commands.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int	call_cmd_for_child(t_cmd *cmd)
{
	int		flag;
	int		built;

	flag = main_redir(cmd->redirs, get_dup_fd());
	if (flag)
		return (1);
	built = check_builtin(cmd);
	if (built)
		return (builtin_work_without_redir(cmd, built));
	return (call_cmd(cmd->argv));
}

int	first_pipe_work(t_cmd **cmd, int *pip, size_t i)
{
	close(pip[0]);
	if (dup2(pip[1], STDOUT_FILENO) == -1)
		return (std_func_err());
	return (call_cmd_for_child(cmd[i]));
}

int	intermediate_pipe_work(t_cmd **cmd, int pipes[2][2], size_t i)
{
	int	*pip;
	int	*pip_next;

	pip = pipes[(i + 1) % 2];
	pip_next = pipes[i % 2];
	close(pip[1]);
	close(pip_next[0]);
	if (dup2(pip[0], STDIN_FILENO) == -1)
		return (std_func_err());
	if (dup2(pip_next[1], STDOUT_FILENO) == -1)
		return (std_func_err());
	return (call_cmd_for_child(cmd[i]));
}

int	last_pipe_work(t_cmd **cmd, int *pip, size_t i)
{
	close(pip[1]);
	if (dup2(pip[0], STDIN_FILENO))
		return (std_func_err());
	return (call_cmd_for_child(cmd[i]));
}

void	start_circle_pipes(t_cmd **cmd, int pip[2][2], size_t i, size_t num)
{
	int	flag;

	flag = 0;
	if (i == 0)
		flag = (first_pipe_work(cmd, pip[0], i));
	else if (i + 1 == num)
		flag = (last_pipe_work(cmd, pip[(i + 1) % 2], i));
	else
		flag = (intermediate_pipe_work(cmd, pip, i));
	exit(flag);
}
