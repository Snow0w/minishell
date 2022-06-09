/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_work.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:41:54 by kirill            #+#    #+#             */
/*   Updated: 2022/06/02 11:47:30 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <commands.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signals.h>

int	simple_call_one_proc(t_cmd **cmd, int minishell)
{
	int		fd[2];
	int		flag;
	pid_t	pid;
	int		status;

	if (prev_dup(fd))
		return (1);
	flag = main_redir((*cmd)->redirs, fd);
	if (flag)
		return (1);
	if (!minishell)
		signals_default();
	pid = fork();
	if (pid == -1)
		return (std_func_err());
	if (pid == 0)
		exit(call_cmd((*cmd)->argv));
	if (waitpid(pid, &status, 0) == -1)
		return (std_func_err());
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	one_command_process(t_cmd **cmd)
{
	int		built;
	pid_t	pid;
	int		status;

	if (!check_minishell_recursive(*cmd))
		return (minishell_recursive(cmd));
	built = check_builtin(*cmd);
	if (built)
		return (simple_builtin_work(cmd, built));
	signals_ignore();
	pid = fork();
	if (pid == -1)
		return (std_func_err());
	if (pid == 0)
		exit(simple_call_one_proc(cmd, 0));
	if (waitpid(pid, &status, 0) == -1)
		return (std_func_err());
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static int	logic_several_com_proc(t_cmd **cmd, size_t num)
{
	size_t	i;
	int		pipes[2][2];
	pid_t	pid;
	pid_t	final_pid;

	i = 0;
	while (i < num)
	{
		if (open_pipes_sev_com(pipes, i, num))
			return (err_pipe_open(pipes, i));
		if (!check_minishell_recursive(cmd[i]))
			signals_ignore();
		else
			signals_default();
		pid = fork();
		if (i == num - 1)
			final_pid = pid;
		if (pid == -1)
			return (err_fork_create(pipes, i));
		if (pid == 0)
			start_circle_pipes(cmd, pipes, i, num);
		close_unused_pipes(pipes, i);
		i++;
	}
	return (waiter(final_pid, num));
}

int	several_com_proc(t_cmd **cmd, size_t num)
{
	int	status;
	int	back_status;

	if (prev_dup(get_dup_fd()))
		return (1);
	status = logic_several_com_proc(cmd, num);
	back_status = put_fd_back(get_dup_fd());
	if (back_status && !status)
		return (back_status);
	return (status);
}

int	pipeline_work(t_cmdtree *tree)
{
	size_t	number;

	if (expand_pipeline(tree->arg1))
		return (set_exit_status(common_err_msg("expand words failed")));
	number = get_cmd_number((t_cmd **) tree->arg1);
	if (number == 0)
		return (set_exit_status(no_command_work((t_cmd **) tree->arg1)));
	if (number == 1)
		return (set_exit_status(one_command_process((t_cmd **) tree->arg1)));
	return (set_exit_status(several_com_proc((t_cmd **) tree->arg1, number)));
}
